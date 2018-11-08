#include "Terrain.h"

#include "Engine/Utils.h"
#include "Engine/Shader.h"
#include "Engine/Camera.h"
#include <fstream>


Terrain::Terrain(Utils::Transform _Transform, Utils::EANCHOR _Anchor)
	:Entity(_Transform, _Anchor)
{
	const char * ImageSource = "Resources/Images/office-square.png";
	mInfo.HeightmapFilename = "Resources/Images/coastMountain513.raw";
	mInfo.NumCols = 513;
	mInfo.NumRows = 513;
	mInfo.HeightScale = 1;
	mInfo.HeightOffset = 0;
	mInfo.CellSpacing = 0;
	loadHeightmap();
	smooth();

	std::vector<GLfloat> ClothVerticies;
	for (int i = 0; i < 120; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			
			// Set Positions for grid
			
			ClothVerticies.push_back(i);
			//Texturedvertices.push_back((float)(rand()%100 - 50)/100);
			ClothVerticies.push_back(mHeightmap[i * mInfo.NumCols + j]);
			ClothVerticies.push_back(j);

			//Setting colour of position on grid
			ClothVerticies.push_back(0.9);
			ClothVerticies.push_back(0.2);
			ClothVerticies.push_back(0.1);
			ClothVerticies.push_back(1);

			//Setting UV Coords
			ClothVerticies.push_back(j/120);
			ClothVerticies.push_back(i/120);
		}

	}
	std::vector<GLuint> indices;

	for (int i = 0; i < 119; i++)
	{
		for (int j = 0; j < 119; j++)
		{
			//Points of the square we're drawing
			int P1, P2, P3, P4;

			//Bottom left corner
			P1 = j * 120 + i;
			//Top Left
			P2 = j * 120 + i + 1;
			//Top Right
			P3 = (j + 1) * 120 + i + 1;
			//Bottom Right
			P4 = (j + 1) * 120 + i ;

			indices.push_back(P1);
			indices.push_back(P2);
			indices.push_back(P3);
			indices.push_back(P1);
			indices.push_back(P3);
			indices.push_back(P4);

		}
	}
	
	// If no texture, texture source is equal to ""
	vao = Shader::CreateBuffer(ImageSource, texture, true);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* ClothVerticies.size(), ClothVerticies.data(), GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), indices.data(), GL_STATIC_DRAW);

	IndiciesCount = indices.size();

	program = Shader::Programs["BaseProgram"];

}


Terrain::~Terrain()
{
}

void Terrain::DrawEntity()
{
	bool Fog = false;
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "bIsTex"), false);
	glUniform1i(glGetUniformLocation(program, "bFog"), false);

	glEnable(GL_BLEND);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);
	Camera::GetInstance()->SetMVP(transform, program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, IndiciesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Terrain::loadHeightmap()
{
	// A height for each vertex
	std::vector<unsigned char> in(mInfo.NumRows * mInfo.NumCols);

	// Open the file.
	std::ifstream inFile;
	inFile.open(mInfo.HeightmapFilename.c_str(), std::ios_base::binary);

	if (inFile)
	{
		// Read the RAW bytes.
		inFile.read((char*)&in[0], (std::streamsize)in.size());

		// Done with file.
		inFile.close();
	}

	// Copy the array data into a float array, and scale and offset the heights.
	mHeightmap.resize(mInfo.NumRows * mInfo.NumCols, 0);
	for (UINT i = 0; i < mInfo.NumRows * mInfo.NumCols; ++i)
	{
		mHeightmap[i] = (float)in[i] * mInfo.HeightScale + mInfo.HeightOffset;
	}
}

void Terrain::smooth()
{
	std::vector<float> dest(mHeightmap.size());

	for (UINT i = 0; i < mInfo.NumRows; ++i)
	{
		for (UINT j = 0; j < mInfo.NumCols; ++j)
		{
			dest[i*mInfo.NumCols + j] = average(i, j);
		}
	}

	// Replace the old heightmap with the filtered one.
	mHeightmap = dest;
}

bool Terrain::inBounds(UINT i, UINT j)
{
	// True if ij are valid indices; false otherwise.
	return
		i >= 0 && i < mInfo.NumRows &&
		j >= 0 && j < mInfo.NumCols;
}

float Terrain::average(UINT i, UINT j)
{
	// Function computes the average height of the ij element.
	// It averages itself with its eight neighbor pixels.  Note
	// that if a pixel is missing neighbor, we just don't include it
	// in the average--that is, edge pixels don't have a neighbor pixel.
	//
	// ----------
	// | 1| 2| 3|
	// ----------
	// |4 |ij| 6|
	// ----------
	// | 7| 8| 9|
	// ----------

	float avg = 0.0f;
	float num = 0.0f;

	for (UINT m = i - 1; m <= i + 1; ++m)
	{
		for (UINT n = j - 1; n <= j + 1; ++n)
		{
			if (inBounds(m, n))
			{
				avg += mHeightmap[m*mInfo.NumCols + n];
				num += 1.0f;
			}
		}
	}

	return avg / num;
}

float Terrain::getHeight(float x, float z)const
{
	// Transform from terrain local space to "cell" space.
	float c = (z);// + 0.5f*width()) / mInfo.CellSpacing;
	float d = (x);// -0.5f*depth()) / -mInfo.CellSpacing;

	// Get the row and column we are in.
	int row = (int)floorf(d);
	int col = (int)floorf(c);

	// Grab the heights of the cell we are in.
	// A*--*B
	//  | /|
	//  |/ |
	// C*--*D
	float A = mHeightmap[row*mInfo.NumCols + col];
	float B = mHeightmap[row*mInfo.NumCols + col + 1];
	float C = mHeightmap[(row + 1)*mInfo.NumCols + col];
	float D = mHeightmap[(row + 1)*mInfo.NumCols + col + 1];

	// Where we are relative to the cell.
	float s = c - (float)col;
	float t = d - (float)row;

	// If upper triangle ABC.
	if (s + t <= 1.0f)
	{
		float uy = B - A;
		float vy = C - A;
		return A + s * uy + t * vy;
	}
	else // lower triangle DCB.
	{
		float uy = C - D;
		float vy = B - D;
		return D + (1.0f - s)*uy + (1.0f - t)*vy;
	}
}