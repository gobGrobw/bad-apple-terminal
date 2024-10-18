#define _DEFAULT_SOURCE
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <dirent.h>
#include <stb_image.h>
#include <unistd.h>
#include <time.h>

// 96x54 resolution (16:9)
#define COLUMN 96
#define ROW 54

int get_frame_count(char *path);
unsigned char *get_image_data(char *file_name);
void print_vframe(unsigned char *arr);

// extract video frames (30 frames per second, aspect ratio 16:9):
// ffmpeg -i "./bad_appuru.mp4" -vf "fps=30,scale=96x54" frame_%04d.jpg

int main()
{
	int frame_count;
	int frame;
	int fps;
	char video_frame[50];
	unsigned char *image_data;
	time_t time, actual_time;
	unsigned int time_diff;

	frame_count = get_frame_count("./video_frames");
	frame = 30;
	fps = 1000000 / frame;
	// Start animation
	// system("mplayer -vo caca bad_appuru.mp4 &"); // Plays video
	system("ffplay -nodisp -autoexit -nostats -hide_banner bad_appuru.wav &"); // Plays audio
	for (int i = 1; i < frame_count; i++)
	{
		time = clock();
		snprintf(video_frame, 50, "./video_frames/frame_%04d.jpg", i);
		image_data = get_image_data(video_frame);

		printf("\033[H"); // Overwrites previous output to prevent flashing
		print_vframe(image_data);
		printf("%s\n", video_frame);

		// Compensate for the time loss
		actual_time = clock();
		time_diff = (unsigned int)(actual_time - time);

		usleep(fps - time_diff);
	}

	return 0;
}

unsigned char *get_image_data(char *file_name)
{
	int width, height, channel;
	unsigned char *pixel_array = stbi_load(file_name, &width, &height, &channel, 1);
	return pixel_array;
}

int get_frame_count(char *path)
{
	int files_count = 0;
	DIR *dir_path = opendir(path);
	struct dirent *entry;

	// readdir gets next file inside dir
	while ((entry = readdir(dir_path)) != NULL)
	{
		if (entry->d_type == DT_REG)
			++files_count;
	}

	closedir(dir_path);
	return files_count;
}

void print_vframe(unsigned char *arr)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			int value = arr[i * COLUMN + j];

			if (value <= 100 && value >= 81)
			{
				printf("//");
			}
			else if (value <= 80 && value >= 61)
			{
				printf("uu");
			}
			else if (value <= 60 && value >= 41)
			{
				printf("oo");
			}
			else
			{
				printf("%s", value <= 40 ? "``" : "@@");
			}
		}
		printf("\n");
	}
}