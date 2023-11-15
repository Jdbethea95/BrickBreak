#ifndef SHADER_AS_STRING_H
#define SHADER_AS_STRING_H

// Reads a file into an std::string 
std::string ReadFileIntoString(const char* filePath);

void PrintLabeledDebugString(const char* label, const char* toPrint);
/// <summary>
/// creates a GVECTORF
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="w">: Set to 1 by default</param>
/// <returns></returns>
GW::MATH::GVECTORF MyVector4(float x, float y, float z, float w = 1);

/// <summary>
/// creates a GVECTORF by calling Vector4 and calls TranslateLocalF
/// </summary>
/// <param name="_matrix"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void MyTranslation(GW::MATH::GMATRIXF& _matrix, float x, float y, float z);


float Degrees2Radians(float degrees);

#endif
