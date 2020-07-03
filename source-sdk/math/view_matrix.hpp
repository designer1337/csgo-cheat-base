#pragma once
#include "vector3d.hpp"

typedef float vec_t;

class view_matrix_t {
public:

	view_matrix_t();
	view_matrix_t(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);

	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	view_matrix_t(const vec3_t& forward, const vec3_t& left, const vec3_t& up);

	// Construct from a 3x4 matrix
	view_matrix_t(const matrix_t& m3x4);

	// Set the values in the matrix.
	void		init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);

	// Initialize from a 3x4
	void		init(const matrix_t& matrix3x4);

	// array access
	inline float* operator[](int i) {
		return m[i];
	}

	inline const float* operator[](int i) const {
		return m[i];
	}

	// Get a pointer to m[0][0]
	inline float* base() {
		return &m[0][0];
	}

	inline const float* base() const {
		return &m[0][0];
	}

	void		set_left(const vec3_t& left);
	void		set_up(const vec3_t& up);
	void		set_forward(const vec3_t& forward);

	void		get_basis_vector_3d(vec3_t& forward, vec3_t& left, vec3_t& up) const;
	void		set_basis_vector_3d(const vec3_t& forward, const vec3_t& left, const vec3_t& up);

	// Get/set the translation.
	vec3_t& 	get_translation(vec3_t& trans) const;
	void		set_translation(const vec3_t& trans);

	void		pre_translate(const vec3_t& tans);
	void		post_translate(const vec3_t& trans);

	matrix_t& 	as_matrix();
	const matrix_t& as_matrix() const;
	void		copy_from_matrix(const matrix_t& m3x4);
	void		set_matrix(matrix_t& m3x4) const;

	bool		operator==(const view_matrix_t& src) const;
	bool		operator!=(const view_matrix_t& src) const { return !(*this == src); }

	// Access the basis vec3_ts.
	vec3_t		get_left() const;
	vec3_t		get_up() const;
	vec3_t		get_forward() const;
	vec3_t		get_translation() const;

	// Matrix->vec3_t operations.
public:
	// Multiply by a 3D vec3_t (same as operator*).
	void		vector_3d_multiply(const vec3_t & in, vec3_t & out) const;

	// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
	vec3_t		apply_rotation(const vec3_t & vec) const;

	// Multiply by a vec3_t (divides by w, assumes input w is 1).
	vec3_t		operator*(const vec3_t & vec) const;

	// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
	vec3_t		vector_3d_multiply(const vec3_t & vec) const;

	// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
	vec3_t		vector_3d_transpose_rotation(const vec3_t & vec) const;

	// Multiply by the upper 3 rows.
	vec3_t		vector_3d_multiply_upper(const vec3_t & vec) const;

	// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
	vec3_t		vector_3d_transpose(const vec3_t & vec) const;
	
public:

	view_matrix_t& operator=(const view_matrix_t & other);

	// Multiply two matrices (out = this * vm).
	void		MatrixMul(const view_matrix_t & vm, view_matrix_t & out) const;

	// Add two matrices.
	const view_matrix_t& operator+=(const view_matrix_t & other);

	// Just calls MatrixMul and returns the result.
	view_matrix_t		operator*(const view_matrix_t & other) const;

	// Add/Subtract two matrices.
	view_matrix_t		operator+(const view_matrix_t & other) const;
	view_matrix_t		operator-(const view_matrix_t & other) const;

	// Negation.
	view_matrix_t		operator-() const;

	// Matrix operations.
public:
	// Set to identity.
	void		identity();

	bool		is_identity() const;

	// Setup a matrix for origin and angles.
	void		setup_maitrx_orginal_angles(const vec3_t & origin, const vec3_t & angles);

	// Does a fast inverse, assuming the matrix only contains translation and rotation.
	void		inverse_tr(view_matrix_t & ret) const;

	// Usually used for debug checks. Returns true if the upper 3x3 contains
	// unit vec3_ts and they are all orthogonal.
	bool		is_rotation_matrix() const;

	// This calls the other InverseTR and returns the result.
	view_matrix_t		inverse_tr() const;

	// Get the scale of the matrix's basis vec3_ts.
	vec3_t			get_scale() const;

	// (Fast) multiply by a scaling matrix setup from vScale.
	view_matrix_t		scale(const vec3_t & scale);

	// Normalize the basis vec3_ts.
	view_matrix_t		normalize_basis_vector_3d() const;

	// Transpose.
	view_matrix_t		transpose() const;

	// Transpose upper-left 3x3.
	view_matrix_t		transpose_3x3() const;

public:
	// The matrix.
	vec_t		m[4][4];
};
