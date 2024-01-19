#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct ImageTask {
    string taskName;
    bool completed;
};
class ImageProcessingTool {
private:
    Mat image;
    vector<ImageTask> tasks;
public:
    ImageProcessingTool(const string& imagePath) {
        // Load an image from file
        image = imread(imagePath);

        if (image.empty()) {
            cerr << "Error: Unable to load image." << endl;
            exit(EXIT_FAILURE);
        }
    }
    void addTask(const string& taskName) {
        tasks.push_back({taskName, false});
        cout << "Task added: " << taskName << endl;
    }
    void displayTasks() {
        cout << "Image Processing Tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].taskName;
            cout << " (" << (tasks[i].completed ? "Completed" : "Pending") << ")" << endl;
        }
    }
    void markTaskAsCompleted(size_t taskIndex) {
        if (taskIndex < tasks.size()) {
            tasks[taskIndex].completed = true;
            cout << "Task marked as completed: " << tasks[taskIndex].taskName << endl;
        } else {
            cerr << "Error: Invalid task index." << endl;
        }
    }
    void removeTask(size_t taskIndex) {
        if (taskIndex < tasks.size()) {
            tasks.erase(tasks.begin() + taskIndex);
            cout << "Task removed." << endl;
        } else {
            cerr << "Error: Invalid task index." << endl;
        }
    }
    void processImage() {
        namedWindow("Original Image", WINDOW_NORMAL);
        imshow("Original Image", image);
        // Wait for a key press
        waitKey(0);
    }
};
int main() {
    string imagePath = "input.jpg";  // Replace with the path to your image
    ImageProcessingTool imageTool(imagePath);

    while (true) {
        cout << "\nImage Processing Tool Menu:" << endl;
        cout << "1. Add Task\n2. View Tasks\n3. Mark Task as Completed\n4. Remove Task\n5. Process Image\n6. Exit\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string taskName;
                cout << "Enter task name: ";
                cin.ignore();  // Clear buffer
                getline(cin, taskName);
                imageTool.addTask(taskName);
                break;
            }
            case 2:
                imageTool.displayTasks();
                break;
            case 3: {
                size_t taskIndex;
                cout << "Enter task index to mark as completed: ";
                cin >> taskIndex;
                imageTool.markTaskAsCompleted(taskIndex - 1);
                break;
            }
            case 4: {
                size_t taskIndex;
                cout << "Enter task index to remove: ";
                cin >> taskIndex;
                imageTool.removeTask(taskIndex - 1);
                break;
            }
            case 5:
                imageTool.processImage();
                break;
            case 6:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cerr << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}