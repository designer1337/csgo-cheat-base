#include "view_matrix.hpp"

view_matrix_t::view_matrix_t() {}

view_matrix_t::view_matrix_t(
	vec_t m00, vec_t m01, vec_t m02, vec_t m03,
	vec_t m10, vec_t m11, vec_t m12, vec_t m13,
	vec_t m20, vec_t m21, vec_t m22, vec_t m23,
	vec_t m30, vec_t m31, vec_t m32, vec_t m33) {
	init(
		m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33
	);
}

view_matrix_t::view_matrix_t(const matrix_t& matrix3x4) {
	init(matrix3x4);
}

//-----------------------------------------------------------------------------
// Creates a matrix where the X axis = forward
// the Y axis = left, and the Z axis = up
//-----------------------------------------------------------------------------
view_matrix_t::view_matrix_t(const vec3_t& _x, const vec3_t& _y, const vec3_t& _z) {
	init(
		_x.x, _y.x, _z.x, 0.0f,
		_x.y, _y.y, _z.y, 0.0f,
		_x.z, _y.z, _z.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void view_matrix_t::init(
	vec_t m00, vec_t m01, vec_t m02, vec_t m03,
	vec_t m10, vec_t m11, vec_t m12, vec_t m13,
	vec_t m20, vec_t m21, vec_t m22, vec_t m23,
	vec_t m30, vec_t m31, vec_t m32, vec_t m33
) {
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;

	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;

	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;

	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

//-----------------------------------------------------------------------------
// Initialize from a 3x4
//-----------------------------------------------------------------------------
void view_matrix_t::init(const matrix_t& m3x4) {
	memcpy(m, m3x4.base(), sizeof(matrix_t));

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

//-----------------------------------------------------------------------------
// vec3_t3DMultiplyPosition treats src2 as if it's a point (adds the translation)
//-----------------------------------------------------------------------------
// NJS: src2 is passed in as a full vec3_t rather than a reference to prevent the need
// for 2 branches and a potential copy in the body.  (ie, handling the case when the src2
// reference is the same as the dst reference ).
void vector_3d_multiply_position(const view_matrix_t& src1, const vec3_t& src2, vec3_t& dst) {
	dst[0] = src1[0][0] * src2.x + src1[0][1] * src2.y + src1[0][2] * src2.z + src1[0][3];
	dst[1] = src1[1][0] * src2.x + src1[1][1] * src2.y + src1[1][2] * src2.z + src1[1][3];
	dst[2] = src1[2][0] * src2.x + src1[2][1] * src2.y + src1[2][2] * src2.z + src1[2][3];
}

//-----------------------------------------------------------------------------
// Methods related to the basis vec3_ts of the matrix
//-----------------------------------------------------------------------------

vec3_t view_matrix_t::get_forward() const {
	return vec3_t(m[0][0], m[1][0], m[2][0]);
}

vec3_t view_matrix_t::get_left() const {
	return vec3_t(m[0][1], m[1][1], m[2][1]);
}

vec3_t view_matrix_t::get_up() const {
	return vec3_t(m[0][2], m[1][2], m[2][2]);
}

void view_matrix_t::set_forward(const vec3_t& forward) {
	m[0][0] = forward.x;
	m[1][0] = forward.y;
	m[2][0] = forward.z;
}

void view_matrix_t::set_left(const vec3_t& left) {
	m[0][1] = left.x;
	m[1][1] = left.y;
	m[2][1] = left.z;
}

void view_matrix_t::set_up(const vec3_t& up) {
	m[0][2] = up.x;
	m[1][2] = up.y;
	m[2][2] = up.z;
}

void view_matrix_t::get_basis_vector_3d(vec3_t& forward, vec3_t& left, vec3_t& up) const {
	forward.init(m[0][0], m[1][0], m[2][0]);
	left.init(m[0][1], m[1][1], m[2][1]);
	up.init(m[0][2], m[1][2], m[2][2]);
}

void view_matrix_t::set_basis_vector_3d(const vec3_t& forward, const vec3_t& left, const vec3_t& up) {
	set_forward(forward);
	set_left(left);
	set_up(up);
}

//-----------------------------------------------------------------------------
// Methods related to the translation component of the matrix
//-----------------------------------------------------------------------------

vec3_t view_matrix_t::get_translation() const {
	return vec3_t(m[0][3], m[1][3], m[2][3]);
}

vec3_t& view_matrix_t::get_translation(vec3_t& trans) const {
	trans.x = m[0][3];
	trans.y = m[1][3];
	trans.z = m[2][3];
	return trans;
}

void view_matrix_t::set_translation(const vec3_t& trans) {
	m[0][3] = trans.x;
	m[1][3] = trans.y;
	m[2][3] = trans.z;
}

//-----------------------------------------------------------------------------
// appply translation to this matrix in the input space
//-----------------------------------------------------------------------------
void view_matrix_t::pre_translate(const vec3_t& trans) {
	vec3_t tmp;
	vector_3d_multiply_position(*this, trans, tmp);
	m[0][3] = tmp.x;
	m[1][3] = tmp.y;
	m[2][3] = tmp.z;
}

//-----------------------------------------------------------------------------
// appply translation to this matrix in the output space
//-----------------------------------------------------------------------------
void view_matrix_t::post_translate(const vec3_t& trans) {
	m[0][3] += trans.x;
	m[1][3] += trans.y;
	m[2][3] += trans.z;
}

const matrix_t& view_matrix_t::as_matrix() const {
	return *((const matrix_t*)this);
}

matrix_t& view_matrix_t::as_matrix() {
	return *((matrix_t*)this);
}

void view_matrix_t::copy_from_matrix(const matrix_t& m3x4) {
	memcpy(m, m3x4.base(), sizeof(matrix_t));
	m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1;
}

void view_matrix_t::set_matrix(matrix_t& m3x4) const {
	memcpy(m3x4.base(), m, sizeof(matrix_t));
}

//-----------------------------------------------------------------------------
// Matrix math operations
//-----------------------------------------------------------------------------
const view_matrix_t& view_matrix_t::operator+=(const view_matrix_t& other) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] += other.m[i][j];
		}
	}
	return *this;
}

view_matrix_t& view_matrix_t::operator=(const view_matrix_t& other) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = other.m[i][j];
		}
	}
	return *this;
}

view_matrix_t view_matrix_t::operator+(const view_matrix_t& other) const {
	view_matrix_t ret;
	for (int i = 0; i < 16; i++) {
		((float*)ret.m)[i] = ((float*)m)[i] + ((float*)other.m)[i];
	}
	return ret;
}

view_matrix_t view_matrix_t::operator-(const view_matrix_t& other) const {
	view_matrix_t ret;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret.m[i][j] = m[i][j] - other.m[i][j];
		}
	}

	return ret;
}

view_matrix_t view_matrix_t::operator-() const {
	view_matrix_t ret;
	for (int i = 0; i < 16; i++) {
		((float*)ret.m)[i] = -((float*)m)[i];
	}
	return ret;
}

//-----------------------------------------------------------------------------
// vec3_t transformation
//-----------------------------------------------------------------------------

vec3_t view_matrix_t::operator*(const vec3_t& vec) const {
	vec3_t ret;
	ret.x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3];
	ret.y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3];
	ret.z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3];
	return ret;
}

vec3_t view_matrix_t::vector_3d_multiply(const vec3_t& vec) const {
	vec3_t result;
	vector_3d_multiply_position(*this, vec, result);
	return result;
}

vec3_t view_matrix_t::vector_3d_transpose(const vec3_t& vec) const {
	vec3_t tmp = vec;
	tmp.x -= m[0][3];
	tmp.y -= m[1][3];
	tmp.z -= m[2][3];

	return vec3_t(
		m[0][0] * tmp.x + m[1][0] * tmp.y + m[2][0] * tmp.z,
		m[0][1] * tmp.x + m[1][1] * tmp.y + m[2][1] * tmp.z,
		m[0][2] * tmp.x + m[1][2] * tmp.y + m[2][2] * tmp.z
	);
}

vec3_t view_matrix_t::vector_3d_multiply_upper(const vec3_t & vec) const {
	return vec3_t(
		m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z,
		m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z,
		m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z
	);
}

vec3_t view_matrix_t::vector_3d_transpose_rotation(const vec3_t & vec) const {
	return vec3_t(
		m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z,
		m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z,
		m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z
	);
}

void view_matrix_t::vector_3d_multiply(const vec3_t & in, vec3_t & out) const {
	vec_t rw;

	rw = 1.0f / (m[3][0] * in.x + m[3][1] * in.y + m[3][2] * in.z + m[3][3]);
	out.x = (m[0][0] * in.x + m[0][1] * in.y + m[0][2] * in.z + m[0][3]) * rw;
	out.y = (m[1][0] * in.x + m[1][1] * in.y + m[1][2] * in.z + m[1][3]) * rw;
	out.z = (m[2][0] * in.x + m[2][1] * in.y + m[2][2] * in.z + m[2][3]) * rw;
}

//-----------------------------------------------------------------------------
// Other random stuff
//-----------------------------------------------------------------------------
void view_matrix_t::identity() {
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

bool view_matrix_t::is_identity() const {
	return
		m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
		m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
		m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f &&
		m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f && m[3][3] == 1.0f;
}

vec3_t view_matrix_t::apply_rotation(const vec3_t & vec) const {
	return vector_3d_multiply(vec);
}
