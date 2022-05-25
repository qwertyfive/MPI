#include <iostream>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <vector>
#include <mpi.h>
#define MAXN 100005
using namespace std;


bool check_point(pair <double, double> Center, double R, pair <double, double> Point) {
    double Len = (Center.first - Point.first) * (Center.first - Point.first) + (Center.second - Point.second) * (Center.second - Point.second);
    Len *= Len;
    return (Len < R);

}
int main(int argc, char* argv[])
{
    pair <double, double> Center;
    double R;
    int n;
    bool ans = 1;
    double Start, Finish, Duration;
    bool done = 0, temp_ans=1;
    double X = 0, Y = 0;
    int ProcRank=0, ProcNum=4;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    cin >> Center.first >> Center.second;
    cin >> R;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    Start = MPI_Wtime();
    scanf("%d", &n);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = ProcRank ; i < n; i += ProcNum) {
        scanf("%f", &X);
        scanf("%f", &Y);
        temp_ans *= check_point(Center, R, make_pair(X,Y));

    }
    MPI_Reduce(&temp_ans, &ans, 1, MPI_DOUBLE, MPI_PROD, 0, MPI_COMM_WORLD);
    Finish = MPI_Wtime();
    if(ans)
        printf("This poligon is inside Circle\n");
    else
        printf("This poligon is not inside Circle\n");
    printf("%f\n", Finish - Start);
    MPI_Finalize();
    return 0;
}
