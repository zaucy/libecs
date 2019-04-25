bazel clean

docker run -it ^
  --entrypoint /bin/bash ^
  --mount type=bind,source="%cd%",target=/root/projects/libecs ^
  --workdir="/root/projects/libecs" ^
  zaucy/bazel:gcc-8
