#include <GLUtil/State.h>

#include <glad/gl.h>

#define ENUM(e) static_cast<GLenum>(e)

namespace GLUtil {

void EnableCapability(Capability cap)
{
	GLUTIL_GL_CALL(glEnable(ENUM(cap)));
}

void EnableCapability(Capability cap, uint32_t index)
{
	GLUTIL_GL_CALL(glEnablei(ENUM(cap), index));
}

void DisableCapability(Capability cap)
{
	GLUTIL_GL_CALL(glDisable(ENUM(cap)));
}

void DisableCapability(Capability cap, uint32_t index)
{
	GLUTIL_GL_CALL(glDisablei(ENUM(cap), index));
}

void SetCapability(Capability cap, bool enabled)
{
	if (enabled)
		EnableCapability(cap);
	else
		DisableCapability(cap);
}

void SetCapability(Capability cap, uint32_t index, bool enabled)
{
	if (enabled)
		EnableCapability(cap, index);
	else
		DisableCapability(cap, index);
}

void GetBool(StateProp pname, unsigned char* value)
{
	GLUTIL_GL_CALL(glGetBooleanv(ENUM(pname), value));
}

void GetBool(StateProp pname, uint32_t index, unsigned char* value)
{
	GLUTIL_GL_CALL(glGetBooleani_v(ENUM(pname), index, value));
}

void GetDouble(StateProp pname, double* value)
{
	GLUTIL_GL_CALL(glGetDoublev(ENUM(pname), value));
}

void GetDouble(StateProp pname, uint32_t index, double* value)
{
	GLUTIL_GL_CALL(glGetDoublei_v(ENUM(pname), index, value));
}

void GetFloat(StateProp pname, float* value)
{
	GLUTIL_GL_CALL(glGetFloatv(ENUM(pname), value));
}

void GetFloat(StateProp pname, uint32_t index, float* value)
{
	GLUTIL_GL_CALL(glGetFloati_v(ENUM(pname), index, value));
}

void GetInt(StateProp pname, int32_t* value)
{
	GLUTIL_GL_CALL(glGetIntegerv(ENUM(pname), value));
}

void GetInt(StateProp pname, uint32_t index, int32_t* value)
{
	GLUTIL_GL_CALL(glGetIntegeri_v(ENUM(pname), index, value));
}

void GetInt64(StateProp pname, int64_t* value)
{
	GLUTIL_GL_CALL(glGetInteger64v(ENUM(pname), value));
}

void GetInt64(StateProp pname, uint32_t index, int64_t* value)
{
	GLUTIL_GL_CALL(glGetInteger64i_v(ENUM(pname), index, value));
}

bool GetBool(StateProp pname)
{
	unsigned char value = 0;
	GetBool(pname, &value);
	return value != 0;
}

bool GetBool(StateProp pname, uint32_t index)
{
	unsigned char value = 0;
	GetBool(pname, index, &value);
	return value != 0;
}

double GetDouble(StateProp pname)
{
	double value = 0;
	GetDouble(pname, &value);
	return value;
}

double GetDouble(StateProp pname, uint32_t index)
{
	double value = 0;
	GetDouble(pname, index, &value);
	return value;
}

float GetFloat(StateProp pname)
{
	float value = 0;
	GetFloat(pname, &value);
	return value;
}

float GetFloat(StateProp pname, uint32_t index)
{
	float value = 0;
	GetFloat(pname, index, &value);
	return value;
}

int32_t GetInt(StateProp pname)
{
	int32_t value = 0;
	GetInt(pname, &value);
	return value;
}

int32_t GetInt(StateProp pname, uint32_t index)
{
	int32_t value = 0;
	GetInt(pname, index, &value);
	return value;
}

int64_t GetInt64(StateProp pname)
{
	int64_t value = 0;
	GetInt64(pname, &value);
	return value;
}

int64_t GetInt64(StateProp pname, uint32_t index)
{
	int64_t value = 0;
	GetInt64(pname, index, &value);
	return value;
}

} // namespace GLUtil