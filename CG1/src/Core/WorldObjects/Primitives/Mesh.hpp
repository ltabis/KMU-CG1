#pragma once

#include "WorldObjects/AShape.hpp"

namespace CG {
	class Mesh : public AShape
	{
	private:
	public:
		Mesh(const std::string &filePath, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
		~Mesh();

		const VertexArray& vao() const override;
		const IndexBuffer& ibo() const override;
	};
}

