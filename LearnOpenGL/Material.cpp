#include "Material.h"

Material::Material(Shader* _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess):
	shader(_shader),
	diffuse(_diffuse),
	specular(_specular),
	ambient(_ambient),
	shininess(_shininess)
{
	
}

void Material::SetTexure(GLuint _diffuse, GLuint _specular)
{
	diffuseTexure = _diffuse;
	specularTexure = _specular;

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _diffuse);
	//glUniform1i(glGetUniformLocation(shader->Program, "material.diffuse"), 0);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, _specular);
	//glUniform1i(glGetUniformLocation(shader->Program, "material.specular"), 1);
}
