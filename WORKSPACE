workspace(name = "com_github_zaucy_libecs")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
	name = "com_google_googletest",
	sha256 = "8268572449b2cf1722826f15e7ddf56bb439c5bcb836513bb1a6b97f4749ca7c",
	url = "https://github.com/google/googletest/archive/1a7732a488850da770943e78ccd6de42985564a1.zip",
	strip_prefix = "googletest-1a7732a488850da770943e78ccd6de42985564a1"
)
# Abseil
http_archive(
	name = "com_google_absl",
	urls = ["https://github.com/abseil/abseil-cpp/archive/master.zip"],
	strip_prefix = "abseil-cpp-master",
)

git_repository(
	name = "bazelregistry_sdl2",
	remote = "https://github.com/bazelregistry/sdl2",
	commit = "e027488f2a6d63cb20c2b63c197742af83025869",
)

git_repository(
	name = "bazelregistry_box2d",
	remote = "https://github.com/bazelregistry/Box2D",
	commit = "02384a43d75635a2d4e0ce32f8625a88fb021e18",
)
