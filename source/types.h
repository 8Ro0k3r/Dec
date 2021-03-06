#ifndef _DEC_TYPES_
#define _DEC_TYPES_

namespace Dec
{
	enum PrimitiveTopology
	{
		POINT_LIST,
		LINE_LIST,
		LINE_STRIP,
		TRIANGLE_LIST,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		LINE_LIST_WITH_ADJACENCY,
		LINE_STRIP_WITH_ADJACENCY,
		TRIANGLE_LIST_WITH_ADJACENCY,
		TRIANGLE_STRIP_WITH_ADJACENCY,
		PATCH_LIST,
	};

	enum ShaderStage
	{
		VERTEX_SHADER = 0,
		TESSELLATION_CONTROL_SHADRER,
		TESSELLATION_EVALUATION_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		SHADER_COUNT
	};

	enum AccessFlags
	{
		CPU_READ = 1,
		CPU_WRITE = CPU_READ << 1,
		CPU_READWRITE = CPU_READ | CPU_WRITE,
		CPU_WRITECOMBINED = CPU_WRITE << 1,
		GPU_READ = CPU_WRITECOMBINED << 1,
		GPU_WRITE = GPU_READ << 1,
		GPU_READWRITE = GPU_READ | GPU_WRITE,
		GPU_EXCUTION = GPU_WRITE << 1
	};	

	enum BufferUsage
	{
		USAGE_READBACK = 0, 
		USAGE_UPLOAD,
		USAGE_UNIFORM_TEXEL,
		USAGE_STORAGE_TEXEL,
		USAGE_UNIFORM,
		USAGE_INDEX,
		USAGE_VERTEX,
		USAGE_FEEDBACK,
		USAGE_FEEDBACK_COUNTER,
		USAGE_CONDITION_RENDERING,
		UASGE_RAY_TRACEING,
		USAGE_SHADER_DEVICE_ADDRESS,
		USAGE_COUNT
	};

	enum TextureType
	{
		Texture1D,
		Texture2D,
		Texture3D,
		TextureCube,
		Texture2DArray
	};

	enum ImageBindFlage
	{
		IMAGE_DEFAULT = 0,
		IMAGE_INPUT,
		IMAGE_STORAGE,
		IMAGE_SAMPLED,
		IMAGE_RENDERTARGET,
		IMAGE_DEPTHSTENCIL,
		IMAGE_DEPTHSTENCIL_READ_ONLY,
		IMAGE_TRANSFER_SRC,
		IMAGE_TRANSFER_DST,
		//IMAGE_PREINITIALIZED,						// Todo : Not support yet
		IMAGE_DEPTH_READ_ONLY_STENCIL,
		IMAGE_Depth_stencil_Read_Only,
		IMAGE_Swapchain,						// Swapchain?
		//IMAGE_SHARED_PRESENT_KHR,					// Todo : Not support yet
		//IMAGE_SHADING_RATE,						// Todo : Not support yet
		//IMAGE_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT,	// Todo : Not support yet
		//IMAGE_DEPTH_READ_ONLY_STENCIL_KHR,		// Todo : Not support yet
		//IMAGE_DEPTH_STENCIL_READ_ONLY_KHR,		// Todo : Not support yet
	};	

	enum SampleCount
	{
		Sample_1,
		Sample_2,
		Sample_4,
		Sample_8,
		Sample_16,
	};

	enum TilingMode
	{
		Linear,
		Tiled
	};

	enum MemoryType
	{
		TYPE_VIRTUAL = 1,
		TYPE_PHYSICAL = TYPE_VIRTUAL << 1,
		TYPE_COMMITTED = TYPE_VIRTUAL | TYPE_PHYSICAL
	};

	enum QueueType
	{
		QUEUE_TYPE_GRAPHICS = 0,
		QUEUE_TYPE_COMPUTE = 1,
		QUEUE_TYPE_COPY = 2
	};

	class GpuFence;
	class CpuFence;
	class CommandList;

	struct SubmitInfo
	{
		U32 WaitFenceCount;
		const GpuFence* WaitFencesPtr;
		U32 SignalFenceCount;
		const GpuFence* SignalFencesPtr;
		U32 CommandBufferCount;
		const CommandList*  CommandBuffersPtr;
		const CpuFence& Fence;
	};

	struct TextureViewCreation
	{

	};
};

#endif // _DEC_TYPES_
