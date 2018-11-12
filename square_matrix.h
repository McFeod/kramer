#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

class AbstractSquareMatrix {
    protected:
        void check(int row, int column);

    public:
        int rank;
        AbstractSquareMatrix(int rank);
        virtual double get(int row, int column) = 0;
        virtual void set(int row, int column, double value) = 0;
};

class SquareMatrix: public AbstractSquareMatrix {
    private:
        bool allocate;
        int flat_index(int row, int column);

    public:
        double get(int row, int column) override;
        void set(int row, int column, double value) override;
        double *representation;
        SquareMatrix(int rank);
        SquareMatrix(int rank, double *items);
        ~SquareMatrix();
};

class SubMatrix: public AbstractSquareMatrix {
    private:
        AbstractSquareMatrix *parent;
        int exclude_row;
        int exclude_column;
        int convert_index(int index, int excluded);

    public:
        SubMatrix(int row, int column, AbstractSquareMatrix *matrix);
        double get(int row, int column) override;
        void set(int row, int column, double value) override;
};

#endif
