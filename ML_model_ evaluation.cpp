#include "ML_model_ evaluation.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3) 
	{
		std::cerr << "Usage: " << argv[0] << " <TestData> <model>" << std::endl;
		return 1;
	}

	cout << "Homework 13: Evaluation the ML model. Used  logistic regression." << endl << endl;

	auto prName = std::string(argv[0]);
	auto testData_fileName = std::string(argv[1]);  // std::string("test.csv");
	auto model_fileName = std::string(argv[2]);     // std::string("logreg_coef.txt");

	// Read model data: matrix 10 x 785
	double modelCoefficients[10][785];

    ifstream modelFile(model_fileName);
    if (!modelFile.is_open()) {
        cerr << "Can't open model file!" << endl;
        return 1;
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 785; ++j) {
            modelFile >> modelCoefficients[i][j];
        }
    }

    modelFile.close();


    int correctPredictions = 0;
    int totalPredictions = 0;

	// Read and check testdata.
    std::ifstream testFile(testData_fileName);
    if (!testFile.is_open()) {
        std::cerr << "Can't open testdata file!" << std::endl;
        return 1;
    }

    std::string line;
    while (getline(testFile, line)) {
        stringstream ss(line);
        string token;

        // Reading the true class (first column).
        int trueClass;
        std::getline(ss, token, ',');
        trueClass = std::stoi(token);

        // Reading pixels (the remaining 784 columns).
        std::array<double, 784> pixels {};
        for (int i = 0; i < 784; ++i) {
            std::getline(ss, token, ',');
            pixels[i] = std::stod(token);
        }

        double maxProbability = -1;
        int predictedClass = -1;

        for (int classIdx = 0; classIdx < 10; ++classIdx) {
            double score = modelCoefficients[classIdx][0]; // Free member.
            for (int i = 0; i < 784; ++i) {
                score += modelCoefficients[classIdx][i + 1] * pixels[i];
            }
            double probability = score;
            
            if (probability > maxProbability) {
                maxProbability = probability;
                predictedClass = classIdx;
            }
        }
        
        if (predictedClass == trueClass) {
            correctPredictions++;
        }
        totalPredictions++;
    }

    testFile.close();

    double accuracy = static_cast<double>(correctPredictions) / totalPredictions;
    std::cout << "Accuracy: " << accuracy * 100 << "%" << std::endl;

	return 0;
}
