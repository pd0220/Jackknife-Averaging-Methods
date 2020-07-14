// include usable functions
#include "Stuff.hh"

// main function
// argv[1] is datafile to fit
//      1st col --> some physical quantity (x)
//      2nd col --> data (y)
//      3rd col --> err (sigma)
// rest of cols --> Jackknife samples (y_jck)
int main(int, char **argv)
{
    // file name
    std::string fileName = "None";
    // check for arguments
    fileName = argv[1];
    
    // error check
    if (fileName == "None")
    {
        std::cout << "No file was given, or the file dose not exist, or unavailable." << std::endl;
        std::exit(-1);
    }

    // read file to matrix
    Eigen::MatrixXd const rawDataMat = ReadFile(fileName);

    // size of raw data
    int rows = rawDataMat.rows(), cols = rawDataMat.cols();

    // x values
    Eigen::VectorXd xData(rows);
    for (int i = 0; i < rows; i++)
    {
        xData(i) = rawDataMat(i, 0);
    }

    // y values
    Eigen::VectorXd yData(rows);
    for (int i = 0; i < rows; i++)
    {
        yData(i) = rawDataMat(i, 1);
    }

    // jackknife samples
    std::vector<Eigen::VectorXd> JCKSamples(cols - 3, Eigen::VectorXd(rows));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < (cols - 3); j++)
        {
            JCKSamples[j](i) = rawDataMat(i, j + 3);
        }
    }
}