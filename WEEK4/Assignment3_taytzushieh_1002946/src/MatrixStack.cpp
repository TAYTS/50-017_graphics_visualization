#include "MatrixStack.h"

MatrixStack::MatrixStack()
{
	// Initialize the matrix stack with the identity matrix.
    m_matrices.push_back(Matrix4f().identity());
}

void MatrixStack::clear()
{
	// Revert to just containing the identity matrix.
    m_matrices.clear();
    m_matrices.push_back(Matrix4f().identity());
}

Matrix4f MatrixStack::top()
{
	// Return the top of the stack, doesnt remove
    return m_matrices.back();
}

void MatrixStack::push( const Matrix4f& m )
{
	// Push m onto the stack.
	// Your stack should have OpenGL semantics:
	// the new top should be the old top multiplied by m
    
    //Doing multiplication
    Matrix4f top = m_matrices.back() * m;
    m_matrices.push_back(top);
}

void MatrixStack::pop()
{
	// Remove the top element from the stack (doesn't return)
    m_matrices.pop_back();
}
