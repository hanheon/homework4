#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);
//함수 선언
//이중포인터를 사용하는 이유는 행렬이 일차원 배열이 나열되어있다고 보기 때문에 값에 접근하기 위해서는 이중포인터 선언을 해야한다.
int main()
{

    char command;
    printf("[----- [HanSeungheon]  [%d] -----]\n", 2020023057);

    int row, col;
    srand(time(NULL)); //난수 생성 함수

    printf("Input row and col : ");  
    scanf("%d %d", &row, &col);  //row와 col 값 입력 받기
    int** matrix_a = create_matrix(row, col);    //matrix_a 행렬 생성1
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");  //행렬 만들어짐.

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);  //커맨드 입력

        switch(command) {
        case 'z': case 'Z':  //행렬 초기화
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);  //a 행렬에 값 할당
            fill_data(matrix_b, row, col);  //b 행렬에 값 할당
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");  
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);  //행렬 전치 명령
            print_matrix(matrix_a_t, col, row);  //전치된 행렬 출력
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");  
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");  //행렬에 할당된 메모리 해제
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) // 행렬 생성 함수
{
    /* check pre conditions */
    if(row <= 0 || col <=0) {
        printf("Check the sizes of row and col!\n");
        return NULL;
        }
        
        int** matrix = (int**)malloc(sizeof(int*) * row);  // 이중포인터의 동적메모리 할당, 배열의 가로
        for (int r = 0; r < row; r++)  // 가로의 크기만큼 반복
        { 
		matrix[r] = (int*)malloc(sizeof(int) * col);  //세로의 크기만큼의 동적할당
	    }


        /* check post conditions */
        if(matrix == NULL) {
            /* proper actions for unexpected conditions */
            }

            return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    /* Check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);   //반복문 활용한 출력문
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)  //2차원 메모리의 공간 메모리 해제 함수
{
/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]);  //1차원 배열이 row개 만큼 있기 때문에 각 배열마다 할당을 해제해야한다.
	}

	free(matrix);
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)  //행렬에 난수 데이터 할당
{
/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) 
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;  //0부터 19까지의 난수 설정해 할당
	/* Check post conditions */
    if (matrix == NULL) 
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);
    /* Check pre conditions */
    if (row <= 0 || col <= 0) 
    {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) 
    {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
        {
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];  //더하기 행렬, 각 원소를 더한 뒤 matrix_sum행렬에 대입, 이 과정을 반복한다.
	    }
    }
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) 
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);  //행렬끼리의 더하기 결과 출력 
	free_matrix(matrix_sum, row, col);  //creat matrix에서 할당받은 메모리 해제
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)  //행렬의 뺄셈
{
int** matrix_sub = create_matrix(row, col);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");  
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++)  
    {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)  
			{
                matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];  // matrix_a - matrix_b, 각 원소를 뺀 뒤 새로운 행렬 matrix_sub에 대입, 이 과정을 반복한다. 
	
            } 
    }
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)  //전치 행렬 함수
{
/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) 
    {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
        {
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];  
        }
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) 
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
int** matrix_axt = create_matrix(row, row);  //a행렬과 전치 행렬 곱하기 함수
	/* Check pre conditions */
	if (row <= 0 || col <= 0) 
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) 
    {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++)      
        {
			int temp = 0;  //누적 변수 초기화
			for (int matrix_col = 0; matrix_col < col; matrix_col++)  
            {
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];   // temp에 두 행렬의 곱한 값을 누적
            }
			matrix_axt[matrix_a_row][matrix_t_row] = temp;  // 곱하기 행렬에 대입해 다시 반복
		}
	}

	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);  //곱한 결과 출력
	free_matrix(matrix_axt, row, col);  
	return 1;
}