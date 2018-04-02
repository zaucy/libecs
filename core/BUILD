cc_library(
	name = "libecs_core",
	include_prefix = "ecs/core/",
	copts = ["/std:c++latest"],
	# copts = ["-std=c++17"],
	hdrs = glob(["**/*.h"]),
	srcs = glob(["**/*.cpp"]) + glob(["**/*.h"]),
	visibility = ["//visibility:public"]
)
