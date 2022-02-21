#include "program.h"

void Program::runProgram(){
    ResultContainer localResultContainer;
    runProgramWithParameters(askForThreadsNumber(),askForPath(), &localResultContainer);
    benchmarkThreads();
    printResults();
}

void Program::runProgramWithParameters(int givenThreadsNumber, string pathOfFolder, ResultContainer *givenResultContainer){
    threadsNumber = givenThreadsNumber;
    path = pathOfFolder;
    resultContainer = givenResultContainer;
    startThreadsPool();
    traverseDirectories();
    stopThreadsPool();
}

void Program::startThreadsPool(){
    threadsPool = new ThreadsPool(threadsNumber);
}

int Program::askForThreadsNumber(){
    int localThreadsNumber = thread::hardware_concurrency();
    
    char setThreads;
    cout<<"Hardware threads number for this system is: "<<localThreadsNumber<<endl;
    cout<<"Do you want to change how many threads will be used?(Y/N) ";
    cin>>setThreads;

    if(setThreads == 'Y'||setThreads == 'y')
    {
        localThreadsNumber=0;
        while(localThreadsNumber==0)
        {
            cout<<"How many threads you want to use? ";
            fflush(stdin);
            cin.clear();
            cin.ignore();
            cin>>localThreadsNumber;
            if(threadsNumber==0) 
                cout<<endl<<"This is not a number. Try again"<<endl;
        }
    }

    return localThreadsNumber;
}

string Program::askForPath(){
    string givenPath;
    cout<<"Precise path in which folders have to be checked"<<endl;
    cout<<"You can write absolute path or relative to file of this program"<<endl;
    cout<<"If no path precised then path of this program will be used"<<endl;
    fflush(stdin);
    cin.clear();
    cin.ignore();
    getline(cin,givenPath);
    std::filesystem::path pathToCheck(std::filesystem::current_path().string()+"\\"+givenPath);
    if(givenPath.empty()){
        cout<<endl<<"No path precised. Path of execution will be used!"<<endl;
        givenPath=std::filesystem::current_path().string();
    }else if(!std::filesystem::exists(pathToCheck)){
        cout<<endl<<"Path does not exist. Path of execution will be used!"<<endl;
        givenPath=std::filesystem::current_path().string();
    }
    return givenPath;
}

void Program::traverseDirectories(){
    
    auto t1 = high_resolution_clock::now();

    threadsPool -> enqueueJob(new DirectoryTraverser (path, threadsPool, resultContainer));

    while(!threadsPool->jobsDone()){}
    auto t2 =high_resolution_clock::now();
    timeUserThreads = t2 - t1;

}

void Program::stopThreadsPool(){
    delete threadsPool;
}

void Program::printResults(){
    cout<<endl<<endl<<"Results:"<<endl;
    cout<<"folders: " << resultContainer -> getFolders() << endl;
    cout<<"files: " << resultContainer -> getFiles() << endl;
    cout<<"total lines: " << ( resultContainer -> getEmptyLines() + resultContainer -> getNonEmptyLines() ) << endl;
    cout<<"empty lines: " << resultContainer -> getEmptyLines() << endl;
    cout<<"words: " << resultContainer -> getWords() << endl;
    cout<<"letters: " << resultContainer -> getLetters() << endl;
    cout<<endl;
    cout<<"Benchmark:"<<endl;
    cout<<"Users "<<threadsNumber<<" thread(s) : "<<timeUserThreads.count()<<"ms"<<endl;
    cout<<"4 threads         : "<<timeFourThreads.count()<<"ms"<<endl;
    cout<<"1 thread          : "<<timeOneThread.count()<<"ms"<<endl;
}

Program::~Program(){
    stopThreadsPool();
}

void Program::benchmarkThreads(){
    ResultContainer tempResultContainer;
    threadsPool = new ThreadsPool(1);
    auto t1 = high_resolution_clock::now();
    threadsPool -> enqueueJob(new DirectoryTraverser(path, threadsPool, &tempResultContainer));
    while(!threadsPool -> jobsDone()){}
    auto t2 = high_resolution_clock::now();
    timeOneThread = t2-t1;
    delete threadsPool;

    threadsPool = new ThreadsPool(4);
    t1 = high_resolution_clock::now();
    threadsPool -> enqueueJob(new DirectoryTraverser(path, threadsPool, &tempResultContainer));
    while(!threadsPool -> jobsDone()){}
    t2 = high_resolution_clock::now();
    timeFourThreads = t2-t1;
    delete threadsPool;
}
