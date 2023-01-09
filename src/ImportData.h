#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex {
	vec3 Pos;
	vec3 Normal;
	vec2 UV;
};

//	Vertex(  顶点数组,  size,  面ID数组,  size,  属性长度数组,  size  )
class ImportData {
private:
	unsigned int  VBO, EBO;
public:	
	unsigned int VAO;
	int sumProp = 0;
	//	Vertex(  顶点数组,  size,  面ID数组,  size,  属性长度数组,  size  )
	ImportData(vector<Vertex> vertices, vector<unsigned int> indices,int prop[],int propSize) {
		
		// ---- VAO, VBO, EBO ----
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);	// 绑定 VAO 
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定VBO
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);// 绑定 EBO 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// 属性Size 累加		
		int* propOffset = new int[propSize];
		int temp = 0;
		for (int i = 0; i < propSize; i++)
		{
			sumProp += prop[i];
			if (i == 0)
				propOffset[i] = 0;
			else
				temp += prop[i - 1];

			propOffset[i] = temp;
		}
		
		for (int i = 0; i < propSize; i++)
		{
			if (i == 0) {
				setProperty(i, prop[i], sumProp, 0);	
			}
			else {
				setProperty(i, prop[i], sumProp, propOffset[i]);
			}
		}

	}


	void setProperty(int pId,int pSize,int vSize,int pOffset)
	{
		glVertexAttribPointer(pId, pSize, GL_FLOAT, GL_FALSE, vSize * sizeof(float), (void*)(pOffset * sizeof(float)));
		glEnableVertexAttribArray(pId);
	}

	// 释放/删除之前的分配的资源
	void deleteBuffer() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

};