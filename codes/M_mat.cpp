template<typename T>
class Matrix {
public:
    vector<vector<T>> mat;
 
    Matrix() {}
 
    Matrix(int _n, int _m, T init) {
        mat = vector<vector<T>>(_n, vector<T>(_m, init));
    }
 
    Matrix(const vector<vector<T>>& a) {
        mat = a;
    }
 
    void set(T init) {
        for(int i = 0; i < rows(); i++) {
            for(int j = 0; j < cols(); j++) {
                mat[i][j] = init;
            }
        }
    }
 
    int rows() const {
        return mat.size();
    }
 
    int cols() const {
        return mat[0].size();
    }
    
    Matrix operator*(const Matrix<T>& obj) const {
        assert(cols() == obj.rows());
        vector<vector<T>> res(rows(), vector<T>(obj.cols()));
        for(int r = 0; r < rows(); r++) {
            for(int c = 0; c < obj.cols(); c++) {
                for(int k = 0; k < cols(); k++) {
                    res[r][c] += mat[r][k] * obj.mat[k][c];
                }
            }
        }
        return res;
    }
 
    vector<T>& operator[](int index) {
        return mat[index];
    }
 
};
 
template<typename T>
ostream& operator<<(ostream& os, Matrix<T>& mat) {
    int n = mat.rows(), m = mat.cols();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            os << mat[i][j] << " ";
        }
        os << endl;
    }
    return os;
}
 
template<typename T>
Matrix<T> power(Matrix<T> res, Matrix<T> a, long long b) {
    while(b > 0) {
        if(b & 1) res = a * res;
        a = a * a;
        b >>= 1;
    }
    return res;
}