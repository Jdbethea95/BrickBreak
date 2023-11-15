
#include "FileIntoString.h"

std::string ReadFileIntoString(const char* filePath)
{
	std::string output;
	unsigned int stringLength = 0;
	GW::SYSTEM::GFile file;

	file.Create();
	file.GetFileSize(filePath, stringLength);

	if (stringLength > 0 && +file.OpenBinaryRead(filePath))
	{
		output.resize(stringLength);
		file.Read(&output[0], stringLength);
	}
	else
		std::cout << "ERROR: File \"" << filePath << "\" Not Found!" << std::endl;

	return output;
}

void PrintLabeledDebugString(const char* label, const char* toPrint)
{
	std::cout << label << toPrint << std::endl;
#if defined WIN32 //OutputDebugStringA is a windows-only function 
	OutputDebugStringA(label);
	OutputDebugStringA(toPrint);
#endif
}

GW::MATH::GVECTORF MyVector4(float x, float y, float z, float w)
{
	GW::MATH::GVECTORF vector = GW::MATH::GVECTORF();
	vector.x = x; vector.y = y; vector.z = z; vector.w = w;
	return vector;
}

void MyTranslation(GW::MATH::GMATRIXF& _matrix, float x, float y, float z)
{
	GW::GReturn ret = GW::GReturn();
	ret = GW::MATH::GMatrix::TranslateLocalF(_matrix, MyVector4(x, y, z), _matrix);
}


float Degrees2Radians(float degrees)
{
	return degrees * (3.141592653589793238463 / 180);
}
