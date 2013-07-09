#ifndef VERTEXHASH_H
#define VERTEXHASH_H

#include <GridVertex.hpp>

class VertexHash: public std::unary_function<const graphs::Vertex&, std::size_t>
{
public:
    int operator()(const graphs::Vertex* vertex) const {
        return std::size_t(vertex->getIndex());
    }
};

#endif // VERTEXHASH_H
