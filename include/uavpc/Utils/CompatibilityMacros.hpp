#define UAVPC_PRAGMA(x) _Pragma(#x)

#ifdef __clang__
#define UAVPC_DISABLE_WARNING(x)      \
  UAVPC_PRAGMA(clang diagnostic push) \
  UAVPC_PRAGMA(clang diagnostic ignored x)
#define UAVPC_END_DISABLE_WARNING UAVPC_PRAGMA(clang diagnostic pop)
#elif __GNUC__
#define UAVPC_DISABLE_WARNING(x)  UAVPC_PRAGMA(GCC diagnostic ignored x)
#define UAVPC_END_DISABLE_WARNING UAVPC_PRAGMA(GCC diagnostic pop)
#endif

#define UAVPC_OPENCV_DISABLE_WARNINGS        \
  UAVPC_DISABLE_WARNING("-Wconversion")      \
  UAVPC_DISABLE_WARNING("-Wold-style-cast")  \
  UAVPC_DISABLE_WARNING("-Wsign-conversion") \
  UAVPC_DISABLE_WARNING("-Wuseless-cast")

#define UAVPC_END_OPENCV_DISABLE_WARNINGS \
  UAVPC_END_DISABLE_WARNING               \
  UAVPC_END_DISABLE_WARNING               \
  UAVPC_END_DISABLE_WARNING               \
  UAVPC_END_DISABLE_WARNING
