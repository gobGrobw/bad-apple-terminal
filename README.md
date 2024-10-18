# bad apple in linux terminal
A small project i made using C



# Running locally
Running locally requires ffmpeg and stb_image.h to be installed

1. Create a directory named **video_frames**
```bash
mkdir video_frames && cd video_frames
```

2. Extract video frames from .mp4 video
You can change the **fps** or **scale** to make it **smoother** or **bigger**
```bash
ffmpeg -i "./bad_appuru.mp4" -vf "fps=30,scale=96x54" frame_%04d.jpg
```

3. Compile and run
```bash
gcc bad_apple.c -o bad_apple -lm && ./bad_apple
```