bazel clean

docker run -it ^
  --entrypoint /bin/bash ^
  --mount type=bind,source="%cd%",target=/root/projects/libecs ^
  --workdir="/root/projects/libecs" ^
  zaucy/bazel:0.15.0-gcc-8
