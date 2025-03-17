#include <stdio.h>

#include "ngiflib.h"
#include "ngiflibSDL.h"

/* define NGIFLIBSDL_LOG to log to stdout */

/* SDL_LoadGIF a le meme comportement que SDL_LoadBMP */
SDL_Surface * SDL_LoadGIF(const char * file)
{
	/* MODE WRAPPER A DEUX BALLES */
	SDL_Surface * surface;
	struct ngiflib_gif * gif;
	FILE *fgif;
	int err,i;
	u8 * pdst, * psrc;
	u8 * p = NULL;
#ifdef NGIFLIB_NO_FILE
	u8 * buffer;
	long filesize;
#endif /* NGIFLIB_NO_FILE */

	fgif = fopen(file, "rb");
	if(fgif==NULL)
		return NULL;
	gif = (struct ngiflib_gif *)ngiflib_malloc(sizeof(struct ngiflib_gif));
	ngiflib_memset(gif, 0, sizeof(struct ngiflib_gif));
#ifdef NGIFLIB_NO_FILE
	fseek(fgif, 0, SEEK_END);
	filesize = ftell(fgif);
	fseek(fgif, 0, SEEK_SET);
	buffer = malloc(filesize);
	if(buffer == NULL) {
		GifDestroy(gif);
		return NULL;
	}
	fread(buffer, 1, filesize, fgif);
	gif->input.bytes = buffer;
	gif->mode = NGIFLIB_MODE_FROM_MEM | NGIFLIB_MODE_INDEXED;
#else /* NGIFLIB_NO_FILE */
	gif->input.file = fgif;
	/*gif->mode = NGIFLIB_MODE_FROM_FILE | NGIFLIB_MODE_TRUE_COLOR; */
	gif->mode = NGIFLIB_MODE_FROM_FILE | NGIFLIB_MODE_INDEXED;
#ifdef NGIFLIBSDL_LOG
	gif->log = stdout;
#endif /* NGIFLIBSDL_LOG */
#endif /* NGIFLIB_NO_FILE */
	err = LoadGif(gif);
	fclose(fgif);
#ifdef NGIFLIB_NO_FILE
	free(buffer);
#endif /* NGIFLIB_NO_FILE */
	if(err!=1)
	{
		GifDestroy(gif);
		return NULL;
	}
	p = gif->frbuff.p8;
	/*
	surface = SDL_CreateRGBSurfaceFrom(p, gif->width, gif->height,
	                                   32, gif->width << 2,
									   0x00ff0000,
									   0x0000ff00,
									   0x000000ff,
									   0xff000000);
	*/
	surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCCOLORKEY,
	                               gif->width, gif->height, 8,
								   0,0,0,0);
	SDL_LockSurface(surface);
	if(gif->cur_img->gce.transparent_flag)
	{
		SDL_SetColorKey(surface, SDL_SRCCOLORKEY, gif->cur_img->gce.transparent_color);
	}
	for(i=0; i<gif->ncolors; i++)
	{
		surface->format->palette->colors[i].r = gif->palette[i].r;
		surface->format->palette->colors[i].g = gif->palette[i].g;
		surface->format->palette->colors[i].b = gif->palette[i].b;
	}
	psrc = p; pdst = surface->pixels;
	for(i=0; i<gif->height; i++)
	{
		ngiflib_memcpy(pdst, psrc, gif->width);
		pdst += surface->pitch;
		psrc += gif->width;
	}
	SDL_UnlockSurface(surface);
	GifDestroy(gif);
	return surface;
}

struct ngiflibSDL_animation * SDL_LoadAnimatedGif(const char * file)
{
	SDL_Surface * surface;
	struct ngiflib_gif * gif;
	FILE *fgif;
	int err,i;
	u8 * pdst, * psrc;
	u8 * p = NULL;
#ifdef NGIFLIB_NO_FILE
	u8 * buffer;
	long filesize;
#endif /* NGIFLIB_NO_FILE */
	int image_count = 0;
	int image_count_max = 50;
	struct ngiflibSDL_animation * animation = NULL;
	struct ngiflib_rgb * current_palette = NULL;
	int current_palette_size = 0;

	fgif = fopen(file, "rb");
	if(fgif==NULL)
		return NULL;
	gif = (struct ngiflib_gif *)ngiflib_malloc(sizeof(struct ngiflib_gif));
	ngiflib_memset(gif, 0, sizeof(struct ngiflib_gif));
#ifdef NGIFLIB_NO_FILE
	fseek(fgif, 0, SEEK_END);
	filesize = ftell(fgif);
	fseek(fgif, 0, SEEK_SET);
	buffer = malloc(filesize);
	if(buffer == NULL) {
		GifDestroy(gif);
		return NULL;
	}
	fread(buffer, 1, filesize, fgif);
	gif->input.bytes = buffer;
	gif->mode = NGIFLIB_MODE_FROM_MEM | NGIFLIB_MODE_INDEXED;
#else /* NGIFLIB_NO_FILE */
	gif->input.file = fgif;
	/*gif->mode = NGIFLIB_MODE_FROM_FILE | NGIFLIB_MODE_TRUE_COLOR; */
	gif->mode = NGIFLIB_MODE_FROM_FILE | NGIFLIB_MODE_INDEXED;
#ifdef NGIFLIBSDL_LOG
	gif->log = stdout;
#endif /* NGIFLIBSDL_LOG */
#endif /* NGIFLIB_NO_FILE */
	while((err = LoadGif(gif)) == 1) {
		if(animation == NULL) {
			animation = ngiflib_malloc(sizeof(struct ngiflibSDL_animation) + image_count_max*sizeof(struct ngiflibSDL_image));
			if(animation == NULL)
				return NULL;
		} else if(image_count >= image_count_max) {
			image_count_max += 50;
			struct ngiflibSDL_animation * tmp;
			tmp = realloc(animation, sizeof(struct ngiflibSDL_animation) + image_count_max*sizeof(struct ngiflibSDL_image));
			if(tmp == NULL) {
				fprintf(stderr, "realloc() failed, cannot decode more images\n");
				break;
			}
			animation = tmp;
		}
		p = gif->frbuff.p8;
		/*
		surface = SDL_CreateRGBSurfaceFrom(p, gif->width, gif->height,
		                                   32, gif->width << 2,
										   0x00ff0000,
										   0x0000ff00,
										   0x000000ff,
										   0xff000000);
		*/
		surface = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCCOLORKEY,
		                               gif->width, gif->height, 8,
									   0,0,0,0);
		SDL_LockSurface(surface);
		/*
		if(gif->transparent_flag) {
			SDL_SetColorKey(surface, SDL_SRCCOLORKEY, gif->transparent_color);
		}
		*/
		if(gif->palette != gif->cur_img->palette) {
			current_palette = gif->cur_img->palette;
			current_palette_size = (1 << gif->cur_img->localpalbits);
		} else if(current_palette == NULL) {
			current_palette = gif->palette;
			current_palette_size = gif->ncolors;
		}
		for(i = 0; i < current_palette_size; i++) {
			surface->format->palette->colors[i].r = current_palette[i].r;
			surface->format->palette->colors[i].g = current_palette[i].g;
			surface->format->palette->colors[i].b = current_palette[i].b;
			//printf("#%02x%02x%02x ",  current_palette[i].r,  current_palette[i].g,  current_palette[i].b);
		}
		for(; i < gif->ncolors; i++) {
			surface->format->palette->colors[i].r = gif->palette[i].r;
			surface->format->palette->colors[i].g = gif->palette[i].g;
			surface->format->palette->colors[i].b = gif->palette[i].b;
			//printf("#%02x%02x%02x ",  gif->palette[i].r,  gif->palette[i].g,  gif->palette[i].b);
		}
		printf("\n");
		psrc = p; pdst = surface->pixels;
		for(i=0; i<gif->height; i++) {
			ngiflib_memcpy(pdst, psrc, gif->width);
			pdst += surface->pitch;
			psrc += gif->width;
		}
		SDL_UnlockSurface(surface);
		animation->images[image_count].delay_time = -1;
		if(gif->cur_img->gce.gce_present) {
			animation->images[image_count].delay_time = gif->cur_img->gce.delay_time;
		}
		animation->images[image_count].surface = surface;
		image_count++;
	}
	fclose(fgif);
#ifdef NGIFLIB_NO_FILE
	free(buffer);
#endif /* NGIFLIB_NO_FILE */
	GifDestroy(gif);
	if(animation) animation->image_count = image_count;
	return animation;
}
