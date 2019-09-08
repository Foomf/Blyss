#pragma once

template<int dimension>
class matrix
{
protected:
    float data_[dimension][dimension] = { 0.0f };

public:
    explicit matrix(float data[dimension][dimension])
    {
        for (size_t row = 0; row < dimension; ++row)
        {
            for (size_t col = 0; col < dimension; ++col)
            {
                data_[row][col] = data[row][col];
            }
        }
    }

    matrix()
    {
        for (size_t row = 0; row < dimension; ++row)
        {
            for (size_t col = 0; col < dimension; ++col)
            {
                data_[row][col] = 0.0f;
            }
        }
    }


    matrix<dimension> operator*(matrix const& rhs) const
    {
        matrix result;

        for (size_t row = 0; row < dimension; ++row)
        {
            for (size_t col = 0; col < dimension; ++col)
            {
                for (size_t ii = 0; ii < dimension; ++ii)
                {
                    result.data_[row][col] += data_[row][ii] * rhs.data_[ii][col];
                }
            }
        }

        return result;
    }

    matrix<dimension> transpose()
    {
        matrix<dimension> new_mat;

        for (size_t row = 0; row < dimension; ++row)
        {
            for (size_t col = 0; col < dimension; ++col)
            {
                new_mat.data_[row][col] = data_[col][row];
            }
        }

        return new_mat;
    }

    float* get_ptr()
    {
        return &data_[0][0];
    }

    auto get()
    {
        return data_;
    }

    static matrix identity()
    {
        float m[dimension][dimension];
        for (size_t x = 0; x < dimension; ++x)
        {
            for (size_t y = 0; y < dimension; ++y)
            {
                m[x][y] = 0.0f;
            }
        }

        for (size_t ii = 0; ii < dimension; ++ii)
        {
            m[ii][ii] = 1.0f;
        }

        return matrix(m);
    }
};