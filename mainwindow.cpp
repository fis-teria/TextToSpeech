//#pragma execution_character_set(“utf-8”)
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ml_window.h"

#define BOOST_PYTHON_STATIC_LIB
#define PY_SSIZE_T_CLEAN
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
#include <boost/python.hpp>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <QString>
#include <QtCore/QDebug>
#include <QMultimedia>
#include <QMediaPlayer>
#include <QtCore/QThread>
#include <QtGui>
#include <QtConcurrent/QtConcurrentRun>
#include <QThread>
#include <QWebEngineView>
#include <QScrollArea>

#include<iostream>
#include<windows.h>

#define PYTHON_EXE_PATH u8"E:\\\\workspace\\\\QtWorkSpace\\\\build\\\\TTS_Release\\\\python\\\\python.exe"

int text_count =1;

// import the main module
boost::python::object main_module;
// load the dictionary object out of the main module
boost::python::object main_namespace;
// run simple code within the main namespace using the boost::python::exec
//  function

ML_Window *win;

// 1024文字まで対応
std::string wchar_to_string(const wchar_t *in_wstr)
{
    size_t convertedChars = 0;
    char str_c[1024];
    wcstombs_s(&convertedChars, str_c, sizeof(str_c), in_wstr, _TRUNCATE);
    std::string out_str = str_c;
    return out_str;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    QPixmap pix("images/tsukuyomichan.png");
    int w = 400;
    int h = 640;
    ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    QFile myFile("log\\log.txt") ;
    if( !myFile.open(QIODevice::ReadOnly | QIODevice::Text) ){
        QMessageBox::information( 0, "FILE IO Error", "Couldn't openFile." ) ;
        return ;
    }
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8") ;
    int tcount=1;
    while (!myFile.atEnd()){
        QString str =  myFile.readLine();
        if(tcount==1){
            ui->label->setText(str);
        }else if(tcount==2){
            ui->label_2->setText(str);
        }else if(tcount==3){
            ui->label_3->setText(str);
        }else if(tcount==4){
            ui->label_4->setText(str);
        }else if(tcount==5){
            ui->label_5->setText(str);
        }else if(tcount==6){
            ui->label_6->setText(str);
        }else if(tcount==7){
            ui->label_7->setText(str);
        }else if(tcount==8){
            ui->label_8->setText(str);
        }else if(tcount==9){
            ui->label_9->setText(str);
        }else if(tcount==10){
            ui->label_10->setText(str);
        }else if(tcount==11){
            ui->label_11->setText(str);
        }else if(tcount==12){
            ui->label_12->setText(str);
        }else if(tcount==13){
            ui->label_13->setText(str);
        }else if(tcount==14){
            ui->label_14->setText(str);
        }else{
            ui->label->setText(ui->label_2->text());
            ui->label_2->setText(ui->label_3->text());
            ui->label_3->setText(ui->label_4->text());
            ui->label_4->setText(ui->label_5->text());
            ui->label_5->setText(ui->label_6->text());
            ui->label_6->setText(ui->label_7->text());
            ui->label_7->setText(ui->label_8->text());
            ui->label_8->setText(ui->label_9->text());
            ui->label_9->setText(ui->label_10->text());
            ui->label_10->setText(ui->label_11->text());
            ui->label_11->setText(ui->label_12->text());
            ui->label_12->setText(ui->label_13->text());
            ui->label_13->setText(ui->label_14->text());
            ui->label_14->setText(str);
        }
        tcount++;
    }
    myFile.close();
    text_count = tcount;


    //MainWindow::BOOST_PYTHON_HELLOWORLD();
    //*/
    std::cout << "a" << std::endl;
}

MainWindow::~MainWindow()
{
    Py_Finalize();
    delete ui;

}

void MainWindow::stack_text(const QString &str){

    if(text_count==1){
        ui->label->setText(str);
    }else if(text_count==2){
        ui->label_2->setText(str);
    }else if(text_count==3){
        ui->label_3->setText(str);
    }else if(text_count==4){
        ui->label_4->setText(str);
    }else if(text_count==5){
        ui->label_5->setText(str);
    }else if(text_count==6){
        ui->label_6->setText(str);
    }else if(text_count==7){
        ui->label_7->setText(str);
    }else if(text_count==8){
        ui->label_8->setText(str);
    }else if(text_count==9){
        ui->label_9->setText(str);
    }else if(text_count==10){
        ui->label_10->setText(str);
    }else if(text_count==11){
        ui->label_11->setText(str);
    }else if(text_count==12){
        ui->label_12->setText(str);
    }else if(text_count==13){
        ui->label_13->setText(str);
    }else if(text_count==14){
        ui->label_14->setText(str);
    }else{
        ui->label->setText(ui->label_2->text());
        ui->label_2->setText(ui->label_3->text());
        ui->label_3->setText(ui->label_4->text());
        ui->label_4->setText(ui->label_5->text());
        ui->label_5->setText(ui->label_6->text());
        ui->label_6->setText(ui->label_7->text());
        ui->label_7->setText(ui->label_8->text());
        ui->label_8->setText(ui->label_9->text());
        ui->label_9->setText(ui->label_10->text());
        ui->label_10->setText(ui->label_11->text());
        ui->label_11->setText(ui->label_12->text());
        ui->label_12->setText(ui->label_13->text());
        ui->label_13->setText(ui->label_14->text());
        ui->label_14->setText(str);
    }
    text_count++;
}

/*
void MainWindow::BOOST_PYTHON_HELLOWORLD(){
    Py_Initialize(); // 最初に呼んでおく必要あり

    try
    {

        // Pythonで「print('Hello World!')」を実行
        boost::python::object global = boost::python::import("__main__").attr("__dict__");
        boost::python::exec("import sys",global);
        boost::python::exec("import os",global);
        boost::python::exec("print(sys.path)",global);
        boost::python::exec("a = os.listdir('./')",global);
        boost::python::exec("print(a)",global);
        //boost::python::exec_file("voice.py", global);
    }
    catch (const boost::python::error_already_set &)
    {
        // Pythonコードの実行中にエラーが発生した場合はエラー内容を表示
        PyErr_Print();
    }
    Py_Finalize();

}
//*/

void BOOST_PYTHON_SETUP(){

    char cdir[255];
    GetCurrentDirectory(255, cdir);
    std::cout << cdir << std::endl;

    wchar_t* program = Py_DecodeLocale(PYTHON_EXE_PATH, NULL);
    std::cout << program << std::endl;
    if (program == nullptr) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
    }else{
        //Py_SetProgramName(program);
        std::cout << wchar_to_string(Py_GetProgramName()) << std::endl;
        //Python のセットアップ
        Py_Initialize();
        try{
            std::cout << wchar_to_string(Py_GetProgramName()) << std::endl;
            std::cout << wchar_to_string(Py_GetPath()) << std::endl;
            std::cout << wchar_to_string(Py_GetPythonHome()) << std::endl;

            ///*
            // import the main module
            main_module = boost::python::import("__main__");
            // load the dictionary object out of the main module
            main_namespace = main_module.attr("__dict__");
            // run simple code within the main namespace using the boost::python::exec
            //  function
            boost::python::exec("print('Hello, world')", main_namespace);
            boost::python::exec("hello = 'hello workd'", main_namespace);
            boost::python::exec("import sys", main_namespace);
            boost::python::exec("import os \n"
                                "print(os.getcwd())", main_namespace);
            boost::python::exec("sys.path.append('tacotron2\\\\')", main_namespace);
            boost::python::exec("sys.path.append('tacotron2\\\\waveglow\\\\')", main_namespace);
            boost::python::exec(("print(sys.path)"), main_namespace);
            boost::python::exec("f = open('debuglog/debug_log.txt', 'w', encoding='UTF-8')", main_namespace);
            boost::python::exec("print('sys path', file=f)", main_namespace);
            boost::python::exec("print(*sys.path, file=f)", main_namespace);
            boost::python::exec("print('current dir', file=f)", main_namespace);
            boost::python::exec("print(*os.getcwd(), file=f)", main_namespace);
            boost::python::exec("f.close()", main_namespace);
            boost::python::exec("import numpy as np", main_namespace);
            boost::python::exec("import torch", main_namespace);
            boost::python::exec("import torchaudio", main_namespace);
            boost::python::exec("import pyopenjtalk", main_namespace);
            boost::python::exec("from hparams_v2 import create_hparams", main_namespace);
            boost::python::exec("from model import Tacotron2", main_namespace);
            boost::python::exec("from layers import TacotronSTFT, STFT", main_namespace);
            boost::python::exec("from audio_processing import griffin_lim", main_namespace);
            boost::python::exec("from train_cpu import load_model", main_namespace);
            boost::python::exec("from text import text_to_sequence", main_namespace);
            boost::python::exec("from denoiser_cpu import Denoiser", main_namespace);
            boost::python::exec("hparams = create_hparams()", main_namespace);
            boost::python::exec("hparams.sampling_rate = 22050", main_namespace);
            boost::python::exec("checkpoint_path = \"tacotron2/outdir3/checkpoint_5000\"", main_namespace);
            boost::python::exec("model = load_model(hparams)", main_namespace);
            boost::python::exec("model.load_state_dict(torch.load(checkpoint_path, map_location=torch.device('cpu'))['state_dict'])", main_namespace);
            //boost::python::exec("_ = model.cuda().eval().float()", main_namespace);
            boost::python::exec("_ = model.to(\"cpu\").eval().float()", main_namespace);
            boost::python::exec("waveglow_path = 'tacotron2/waveglow_256channels_universal_v5.pt'", main_namespace);
            boost::python::exec("waveglow = torch.load(waveglow_path)['model']", main_namespace);
            //boost::python::exec("waveglow.cuda().eval().float()", main_namespace);
            boost::python::exec("waveglow.to(\"cpu\").eval().float()", main_namespace);
            boost::python::exec("for k in waveglow.convinv:\n"
                                "    k.float()", main_namespace);
            boost::python::exec("", main_namespace);
            boost::python::exec("denoiser = Denoiser(waveglow)", main_namespace);

        }catch (const boost::python::error_already_set &)
        {
            // Pythonコードの実行中にエラーが発生した場合はエラー内容を表示
            PyErr_Print();
        }
    }

}

void BOOST_PYTHON_VOICE_INFERENCE(QString &str){
    //Py_Initialize(); // 最初に呼んでおく必要あり
    QFile fpFile("read\\read_up.txt");
    fpFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&fpFile);
    stream.setCodec("UTF-8");
    stream << str << Qt::endl;
    fpFile.close();


    try
    {
        boost::python::exec("str = open('read/read_up.txt', 'r', encoding='UTF-8')", main_namespace);
        boost::python::exec("text = str.read()", main_namespace);
        boost::python::exec("str.close()", main_namespace);
        boost::python::exec("phones = pyopenjtalk.g2p(text, kana=False)", main_namespace);
        boost::python::exec("phones = phones.replace('pau',',')", main_namespace);
        boost::python::exec("phones = phones.replace(' ','')", main_namespace);
        boost::python::exec("phones = phones + '.'", main_namespace);
        boost::python::exec("sequence = np.array(text_to_sequence(phones, ['basic_cleaners']))[None, :]", main_namespace);
        boost::python::exec("#sequence = np.array(text_to_sequence(text, ['english_cleaners']))[None, :]", main_namespace);
        boost::python::exec("sequence = torch.autograd.Variable(\n"
                            //                    "    torch.from_numpy(sequence)).cuda().long()", main_namespace);
                            "    torch.from_numpy(sequence)).to(\"cpu\").long()", main_namespace);
        boost::python::exec("", main_namespace);
        boost::python::exec("mel_outputs, mel_outputs_postnet, _, alignments = model.inference(sequence)", main_namespace);
        boost::python::exec("mel_outputs = mel_outputs.to(torch.float32)", main_namespace);
        boost::python::exec("mel_outputs_postnet = mel_outputs_postnet.to(torch.float32)", main_namespace);
        boost::python::exec("_ = _.to(torch.float32)", main_namespace);
        boost::python::exec("alignments = alignments.to(torch.float32)", main_namespace);
        boost::python::exec("data = [mel_outputs.float().data.cpu().numpy()[0], mel_outputs_postnet.float().data.cpu().numpy()[0], alignments.float().data.cpu().numpy()[0].T]", main_namespace);
        boost::python::exec("with torch.no_grad():\n"
                            "    audio = waveglow.infer_cpu(mel_outputs_postnet, sigma=0.666)", main_namespace);
        boost::python::exec("", main_namespace);
        boost::python::exec("", main_namespace);
        std::cout << "output mp3" << std::endl;
        boost::python::exec("audio_tensor = torch.from_numpy(audio[0].data.cpu().numpy())", main_namespace);
        boost::python::exec("audio_tensor = audio_tensor.unsqueeze(0)  # 2次元のテンソルに変換", main_namespace);
        boost::python::exec("audio_tensor = audio_tensor.to(torch.float32)", main_namespace);
        boost::python::exec("print(audio_tensor)", main_namespace);
        boost::python::exec("torchaudio.save(uri='result.mp3', src=audio_tensor, sample_rate=hparams.sampling_rate, format='mp3')", main_namespace);
        QMediaPlayer *player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile("result.mp3"));
        player->setVolume(100);
        player->play();
        QThread::sleep(7);
        delete(player);
    }
    catch (const boost::python::error_already_set &)
    {
        // Pythonコードの実行中にエラーが発生した場合はエラー内容を表示
        PyErr_Print();
    }

}


void MainWindow::on_GoTTS_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
}


void MainWindow::on_back_start_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_lineEdit_returnPressed()
{
    QString str = ui->lineEdit->text();
    stack_text(str);
    ui->lineEdit->clear();

    QFile fpFile("log\\log.txt");
    fpFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream stream(&fpFile);
    stream.setCodec("UTF-8");
    stream << str << Qt::endl;
    fpFile.close();
    QFuture<void> job = QtConcurrent::run(BOOST_PYTHON_VOICE_INFERENCE, str);
    job.waitForFinished();
    //BOOST_PYTHON_VOICE_INFERENCE(str);

}




void MainWindow::on_credit_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_2_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    if(arg1 == 2){
        BOOST_PYTHON_SETUP();
    }
    if(arg1 == 3){

    }
}



void MainWindow::on_GoML_clicked()
{
    win = new ML_Window(this);

    ui->stackedWidget->setCurrentIndex(3);
    win->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    win->close();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_GoData_clicked()
{
    for(int i = 0; i< 100;i++){

    }
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

