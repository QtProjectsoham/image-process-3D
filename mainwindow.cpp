#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<math.h>
#define d1 3
#define d2 4
#define d3 5
#define xdimen 300
#define ydimen 300
#define zdimen 300
struct node
{
    int data;
    struct node *next;
};
//QRgb cclcolormap[12];
unsigned short readShort(FILE *inff);
int ipimg[xdimen][ydimen][zdimen],binarize[xdimen][ydimen][zdimen],a[xdimen][ydimen][zdimen],hist[xdimen][ydimen][zdimen],ccl[xdimen][ydimen][zdimen],component[12],cc=0;
bool inputimg=false, dtimg=false, cclimg=false,fdtimg=false,bin=false,hg=false;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadimage_clicked()
{
    int sx;
    QString temp;
    temp=QFileDialog::getOpenFileName(this,tr("Open File"), "",
                                      tr("Analyze Images (*.hdr)"));

    QFileInfo f(temp);
    base=f.baseName();
    str=base.toStdString();
    str=str+".img";
    ch=str.c_str();
    //base=base+".img";
    //base=(const char *)base;
    QByteArray qb=temp.toLatin1();
    filename =  qb.data();

   ui->ipfilename->setText(base);
   histogram();
   ui->slider_x->setRange(0,Xdim-1);
   ui->slider_y->setRange(0,Ydim-1);
   ui->slider_z->setRange(0,Zdim-1);
   ui->spinBox_x->setRange(0,Xdim-1);
   ui->spinBox_y->setRange(0,Ydim-1);
   ui->spinBox_z->setRange(0,Zdim-1);
   ui->slider_x->setValue(Xdim/2);
   ui->slider_y->setValue(Ydim/2);
   ui->slider_z->setValue(Zdim/2);
   ui->spinBox_x->setValue(Xdim/2);
   ui->spinBox_y->setValue(Ydim/2);
   ui->spinBox_z->setValue(Zdim/2);
   curX=ui->spinBox_x->value();
   curY=ui->spinBox_y->value();
   curZ=ui->spinBox_z->value();
   //ui->xdimension->setNum(sx);
   readimage();

}
void MainWindow::histogram()
{
  void *hdr;
  Xdim=0;
  Ydim=0;
  Zdim=0;
  FILE *fo;
  //char buffer[100];
  hdr=malloc(480);

  fo = fopen(filename, "rb");

  //unsigned short uns[3];

  if(fo)
  {

      fread(hdr,348,1,fo);

      fseek(fo,42,SEEK_SET);
      Xdim=(int)readShort(fo);
      Ydim=(int)readShort(fo);
      Zdim=(int)readShort(fo);

  }
  fclose(fo);
  ui->xdimension->setNum(Xdim);
  ui->ydimension->setNum(Ydim);
  ui->zdimension->setNum(Zdim);
}
unsigned short readShort( FILE* inff )     // read a 16 bit integer
{

    unsigned short ret;
    unsigned char lowByte, hiByte;


    lowByte = fgetc(inff);         // Read the low order byte (little endian form)
    hiByte = fgetc(inff);          // Read the high order byte
    ret = hiByte;
    ret <<= 8;
    ret |= lowByte;

    return ret;

    //std::cout<<"readShort() ended"<<std::endl;
}
void MainWindow::readimage()
{
   int i,j,k;
   FILE *fp;
   unsigned short pixel;
   fp=fopen(ch,"rb");
   if(!fp)
   {
       printf("\n Unable to open file");
       exit(0);
   }
   for(k=0;k<Zdim;k++)        // read the image
   {
       for(j=0;j<Ydim;j++)
       {
           for(i=0;i<Xdim;i++)
           {
               if(fread(&pixel,sizeof(unsigned short),1,fp)==1)
               {
                   ipimg[i][j][k]=pixel;
               }
           }
       }
   }
     inputimg=true;bin=false;dtimg=false;cclimg=false;fdtimg=false;
     drawimage();
}
void MainWindow::drawimage()
{
    int i,j;
    unsigned short value1;
    QImage opimg_XY(Xdim,Ydim,QImage::Format_RGB32);
    QImage opimg_XZ(Xdim,Zdim,QImage::Format_RGB32);
    QImage opimg_YZ(Ydim,Zdim,QImage::Format_RGB32);
    QRgb value;
    if(inputimg==true)
    {
    for(j=0;j<Ydim;j++)
    {
        for(i=0;i<Xdim;i++)
        {
            value1=ipimg[i][j][curZ];
            value=qRgb(value1,value1,value1);
            opimg_XY.setPixel(QPoint(i,j),value);
        }
    }
    ui->label_XY->setPixmap(QPixmap::fromImage(opimg_XY));

    for(j=0;j<Zdim;j++)
    {
        for(i=0;i<Xdim;i++)
        {
            value1=ipimg[i][curY][j];
            value=qRgb(value1,value1,value1);
            opimg_XZ.setPixel(QPoint(i,j),value);
        }
    }
    ui->label_XZ->setPixmap(QPixmap::fromImage(opimg_XZ));
    for(j=0;j<Zdim;j++)
     {
         for(i=0;i<Ydim;i++)
         {
             value1=ipimg[curX][i][j];
             value=qRgb(value1,value1,value1);
             opimg_YZ.setPixel(QPoint(i,j),value);
         }
     }
     ui->label_YZ->setPixmap(QPixmap::fromImage(opimg_YZ));
    }
    else if(bin==true)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=binarize[i][j][curZ];
                value=qRgb(value1,value1,value1);
                opimg_XY.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XY->setPixmap(QPixmap::fromImage(opimg_XY));

        for(j=0;j<Zdim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=binarize[i][curY][j];
                value=qRgb(value1,value1,value1);
                opimg_XZ.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XZ->setPixmap(QPixmap::fromImage(opimg_XZ));
        for(j=0;j<Zdim;j++)
         {
             for(i=0;i<Ydim;i++)
             {
                 value1=binarize[curX][i][j];
                 value=qRgb(value1,value1,value1);
                 opimg_YZ.setPixel(QPoint(i,j),value);
             }
         }
         ui->label_YZ->setPixmap(QPixmap::fromImage(opimg_YZ));
    }
    else if(dtimg==true)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=a[i][j][curZ];
                value=qRgb(value1,value1,value1);
                opimg_XY.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XY->setPixmap(QPixmap::fromImage(opimg_XY));

        for(j=0;j<Zdim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=a[i][curY][j];
                value=qRgb(value1,value1,value1);
                opimg_XZ.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XZ->setPixmap(QPixmap::fromImage(opimg_XZ));
        for(j=0;j<Zdim;j++)
         {
             for(i=0;i<Ydim;i++)
             {
                 value1=a[curX][i][j];
                 value=qRgb(value1,value1,value1);
                 opimg_YZ.setPixel(QPoint(i,j),value);
             }
         }
         ui->label_YZ->setPixmap(QPixmap::fromImage(opimg_YZ));
    }
    else if(cclimg=true)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=ccl[i][j][curZ];

                value=qRgb(value1,value1,value1);
                opimg_XY.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XY->setPixmap(QPixmap::fromImage(opimg_XY));

        for(j=0;j<Zdim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=ccl[i][curY][j];
                if(value1!=0)
                {
                    if(value1!=2)
                    {
                        value=qRgb(255,0,0);
                    }
                    else
                    {
                        value=qRgb(0,0,255);
                    }
                }
                else
                {
                    value=qRgb(0,0,0);
                }
                opimg_XZ.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XZ->setPixmap(QPixmap::fromImage(opimg_XZ));
        for(j=0;j<Zdim;j++)
         {
             for(i=0;i<Ydim;i++)
             {
                 value1=ccl[curX][i][j];
                 if(value1!=0)
                 {
                     if(value1!=2)
                     {
                         value=qRgb(255,0,0);
                     }
                     else
                     {
                         value=qRgb(0,0,255);
                     }
                 }
                 else
                 {
                     value=qRgb(0,0,0);
                 }
                 opimg_YZ.setPixel(QPoint(i,j),value);
             }
         }
         ui->label_YZ->setPixmap(QPixmap::fromImage(opimg_YZ));
    }
}

void MainWindow::on_spinBox_x_valueChanged(int arg1)
{
    curX=arg1;
    ui->xdimension->setNum(curX);
    drawimage_YZ();
}

void MainWindow::on_spinBox_y_valueChanged(int arg2)
{
    curY=arg2;
    ui->ydimension->setNum(curY);
    drawimage_XZ();
}

void MainWindow::on_spinBox_z_valueChanged(int arg3)
{
    curZ=arg3;
    ui->zdimension->setNum(curZ);
    drawimage_XY();
}

void MainWindow::drawimage_XY()
{
    int i,j;
    unsigned short value1;
    QImage opimg_XY(Xdim,Ydim,QImage::Format_RGB32);
    QRgb value;
    if(inputimg==true)
    {
    for(j=0;j<Ydim;j++)
    {
        for(i=0;i<Xdim;i++)
        {
            value1=ipimg[i][j][curZ];
            value=qRgb(value1,value1,value1);
            opimg_XY.setPixel(QPoint(i,j),value);
        }
    }
    ui->label_XY->setPixmap(QPixmap::fromImage(opimg_XY));
    }
    else if(bin==true)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=binarize[i][j][curZ];
                value=qRgb(value1,value1,value1);
                opimg_XY.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XY->setPixmap(QPixmap::fromImage(opimg_XY));
    }
    else if(dtimg==true)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=a[i][j][curZ];
                value=qRgb(value1,value1,value1);
                opimg_XY.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XY->setPixmap(QPixmap::fromImage(opimg_XY));
    }
    else if(cclimg==true)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=ccl[i][j][curZ];
                if(value1!=0)
                {
                      if(cc==1)
                      {
                       value=qRgb(0,0,255);
                      }
                      else if(cc==2)
                      {
                        if(value1==2)
                        value=qRgb(0,0,255);
                        else
                        value=qRgb(255,0,0);
                      }
                      else if(cc==3)
                      {

                      }
                }
                else
                {
                  value=qRgb(0,0,0);
                }
                opimg_XY.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XY->setPixmap(QPixmap::fromImage(opimg_XY));
    }
}

void MainWindow::drawimage_XZ()
{
    int i,j;
    unsigned short value1;
    QImage opimg_XZ(Xdim,Zdim,QImage::Format_RGB32);
    QRgb value;
    if(inputimg==true)
    {
    for(j=0;j<Zdim;j++)
    {
        for(i=0;i<Xdim;i++)
        {
            value1=ipimg[i][curY][j];
            value=qRgb(value1,value1,value1);
            opimg_XZ.setPixel(QPoint(i,j),value);
        }
    }
    ui->label_XZ->setPixmap(QPixmap::fromImage(opimg_XZ));
    }
    else if(bin==true)
    {
        for(j=0;j<Zdim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=binarize[i][curY][j];
                value=qRgb(value1,value1,value1);
                opimg_XZ.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XZ->setPixmap(QPixmap::fromImage(opimg_XZ));
    }
    else if(dtimg==true)
    {
        for(j=0;j<Zdim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=a[i][curY][j];
                value=qRgb(value1,value1,value1);
                opimg_XZ.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XZ->setPixmap(QPixmap::fromImage(opimg_XZ));
    }
    else if(cclimg==true)
    {
        for(j=0;j<Zdim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                value1=ccl[i][curY][j];
                if(value1!=0)
                {
                      if(cc==1)
                      {
                       value=qRgb(0,0,255);
                      }
                      else if(cc==2)
                      {
                        if(value1==2)
                        value=qRgb(0,0,255);
                        else
                        value=qRgb(255,0,0);
                      }
                      else if(cc==3)
                      {

                      }
                }
                else
                {
                  value=qRgb(0,0,0);
                }
                opimg_XZ.setPixel(QPoint(i,j),value);
            }
        }
        ui->label_XZ->setPixmap(QPixmap::fromImage(opimg_XZ));
    }
}

void MainWindow::drawimage_YZ()
{
    int i,j;
    unsigned short value1;
     QImage opimg_YZ(Ydim,Zdim,QImage::Format_RGB32);
     QRgb value;
     if(inputimg==true)
     {
     for(j=0;j<Zdim;j++)
     {
         for(i=0;i<Ydim;i++)
         {
             value1=ipimg[curX][i][j];
             value=qRgb(value1,value1,value1);
             opimg_YZ.setPixel(QPoint(i,j),value);
         }
     }
     ui->label_YZ->setPixmap(QPixmap::fromImage(opimg_YZ));
     }
     else if(bin==true)
     {
         for(j=0;j<Zdim;j++)
         {
             for(i=0;i<Ydim;i++)
             {
                 value1=binarize[curX][i][j];
                 value=qRgb(value1,value1,value1);
                 opimg_YZ.setPixel(QPoint(i,j),value);
             }
         }
         ui->label_YZ->setPixmap(QPixmap::fromImage(opimg_YZ));
     }
     else if(dtimg==true)
     {
         for(j=0;j<Zdim;j++)
         {
             for(i=0;i<Ydim;i++)
             {
                 value1=a[curX][i][j];
                 value=qRgb(value1,value1,value1);
                 opimg_YZ.setPixel(QPoint(i,j),value);
             }
         }
         ui->label_YZ->setPixmap(QPixmap::fromImage(opimg_YZ));
     }
     else if(cclimg==true)
     {
         for(j=0;j<Zdim;j++)
         {
             for(i=0;i<Ydim;i++)
             {
                 value1=ccl[curX][i][j];
                 if(value1!=0)
                 {
                       if(cc==1)
                       {
                        value=qRgb(0,0,255);
                       }
                       else if(cc==2)
                       {
                         if(value1==2)
                         value=qRgb(0,0,255);
                         else
                         value=qRgb(255,0,0);
                       }
                       else if(cc==3)
                       {

                       }
                 }
                 else
                 {
                   value=qRgb(0,0,0);
                 }
                 opimg_YZ.setPixel(QPoint(i,j),value);
             }
         }
         ui->label_YZ->setPixmap(QPixmap::fromImage(opimg_YZ));
     }
}

void MainWindow::on_binarize_clicked()
{
    int i,j,k;
    for(k=0;k<Zdim;k++)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                if(ipimg[i][j][k]!=0)binarize[i][j][k]=255;
                else
                    ipimg[i][j][k]=0;
            }
        }
    }
    bin=true,dtimg=false;fdtimg=false,cclimg=false,inputimg=false,hg=false;
    drawimage();
}

void MainWindow::on_DT_clicked()
{
    int i,j,k,min;
    int flag1;
    double v;
    unsigned short maxintendt=0;
    for(k=0;k<Zdim;k++)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                if(ipimg[i][j][k]!=0)a[i][j][k]=65500;
                else
                    a[i][j][k]=0;
            }
        }
    }
    do
    {
        flag1=0;
        for(k=0;k<Zdim;k++)   //forward pass
            {
                for(j=0;j<Ydim;j++)
                {
                    for(i=0;i<Xdim;i++)
                    {
                        if(a[i][j][k]!=0)
                        {
                            min=a[i][j][k];
                            if((i-1>=0)&&((a[i-1][j][k]+d1)<min))
                            {
                                min=a[i-1][j][k]+d1;
                                flag1++;
                            }
                            if((i-1>=0)&&(j-1>=0)&&((a[i-1][j-1][k]+d2)<min))
                            {
                                min=a[i-1][j-1][k]+d2;
                                flag1++;
                            }
                            if((j-1>=0)&&((a[i][j-1][k]+d1)<min))
                            {
                                min=a[i][j-1][k]+d1;
                                flag1++;
                            }
                            if((i+1<Xdim)&&(j-1>=0)&&((a[i+1][j-1][k]+d2)<min))
                            {
                                min=a[i+1][j-1][k]+d2;
                                flag1++;
                            }
                            if((k+1<Zdim)&&((a[i][j][k+1]+d1)<min))
                            {
                               min=a[i][j][k+1]+d1;
                               flag1++;
                            }
                            if((k+1<Zdim)&&(j-1>=0)&&((a[i][j-1][k+1]+d2)<min))
                            {
                               min=a[i][j-1][k+1]+d2;
                               flag1++;
                            }
                            if((k+1<Zdim)&&(j+1<Ydim)&&((a[i][j+1][k+1]+d2)<min))
                            {
                               min=a[i][j+1][k+1]+d2;
                               flag1++;
                            }
                            if((k+1<Zdim)&&(i-1>=0)&&((a[i-1][j][k+1]+d2)<min))
                            {
                               min=a[i-1][j][k+1]+d2;
                               flag1++;
                            }
                            if((k+1<Zdim)&&(j-1>=0)&&(i-1>=0)&&((a[i-1][j-1][k+1]+d3)<min))
                            {
                               min=a[i-1][j-1][k+1]+d3;
                               flag1++;
                            }
                            if((k+1<Zdim)&&(j+1<Ydim)&&(i-1>=0)&&((a[i-1][j+1][k+1]+d3)<min))
                            {
                               min=a[i-1][j+1][k+1]+d3;
                               flag1++;
                            }
                            if((k+1<Zdim)&&(i+1<Xdim)&&((a[i+1][j][k+1]+d2)<min))
                            {
                               min=a[i+1][j][k+1]+d2;
                               flag1++;
                            }
                            if((k+1<Zdim)&&(j-1>=0)&&(i+1<Xdim)&&((a[i+1][j-1][k+1]+d3)<min))
                            {
                               min=a[i+1][j-1][k+1]+d3;
                               flag1++;
                            }
                            if((k+1<Zdim)&&(j+1<Ydim)&&(i+1<Xdim)&&((a[i+1][j+1][k+1]+d3)<min))
                            {
                               min=a[i+1][j+1][k+1]+d3;
                               flag1++;
                            }

                            a[i][j][k]=min;
                            if(min>maxintendt)maxintendt=min;
                        }
                    }
                }
            }
            for(k=Zdim-1;k>=0;k--)         //Backward Pass
            {
                for(j=Ydim-1;j>=0;j--)
                {
                    for(i=Xdim-1;i>=0;i--)
                    {
                        if(a[i][j][k]!=0)
                        {
                            min=a[i][j][k];
                            if((i+1<Xdim)&&((a[i+1][j][k]+d1)<min))
                            {
                                min=a[i+1][j][k]+d1;
                                flag1++;
                            }
                            if((j+1<Ydim)&&((a[i][j+1][k]+d1)<min))
                            {
                                min=a[i][j+1][k]+d1;
                                flag1++;
                            }
                            if((i-1>=0)&&(j+1<Ydim)&&((a[i-1][j+1][k]+d2)<min))
                            {
                                min=a[i-1][j+1][k]+d2;
                                flag1++;
                            }
                            if((i+1<Xdim)&&(j+1<Ydim)&&((a[i+1][j+1][k]+d2)<min))
                            {
                                min=a[i+1][j+1][k]+d2;
                                flag1++;
                            }
                            if((k-1>=0)&&((a[i][j][k-1]+d1)<min))
                            {
                                min=a[i][j][k-1]+d1;
                                flag1++;
                            }
                            if((k-1>=0)&&(i-1>=0)&&((a[i-1][j][k-1]+d2)<min))
                            {
                                min=a[i-1][j][k-1]+d2;
                                flag1++;
                            }
                            if((k-1>=0)&&(i+1<Xdim)&&((a[i+1][j][k-1]+d2)<min))
                            {
                                min=a[i+1][j][k-1]+d2;
                                flag1++;
                            }
                            if((k-1>=0)&&(i-1>=0)&&(j-1>=0)&&((a[i-1][j-1][k-1]+d3)<min))
                            {
                                min=a[i-1][j-1][k-1]+d3;
                                flag1++;
                            }
                            if((k-1>=0)&&(j-1>=0)&&((a[i][j-1][k-1]+d2)<min))
                            {
                                min=a[i][j-1][k-1]+d2;
                                flag1++;
                            }
                            if((k-1>=0)&&(i+1<Xdim)&&(j-1>=0)&&((a[i+1][j-1][k-1]+d3)<min))
                            {
                                min=a[i+1][j-1][k-1]+d3;
                                flag1++;
                            }
                            if((k-1>=0)&&(j+1<Ydim)&&((a[i][j+1][k-1]+d2)<min))
                            {
                                min=a[i][j+1][k-1]+d2;
                                flag1++;
                            }
                            if((k-1>=0)&&(i-1>=0)&&(j+1<Ydim)&&((a[i-1][j+1][k-1]+d3)<min))
                            {
                                min=a[i-1][j+1][k-1]+d3;
                                flag1++;
                            }
                            if((k-1>=0)&&(j+1<Ydim)&&(i+1<Xdim)&&((a[i+1][j+1][k-1]+d3)<min))
                            {
                                min=a[i+1][j+1][k-1]+d3;
                                flag1++;
                            }
                            a[i][j][k]=min;
                            if(min>maxintendt)maxintendt=min;
                        }
                    }
                }
            }
            /*printf("%d ",flag1);
            if(flag1!=0)
                printf("one iteration complete\n");*/
    }while(flag1!=0);
    for(k=0;k<Zdim;k++)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                        v=round((a[i][j][k]/(double)maxintendt)*255);
                        a[i][j][k]=v;
            }
        }
    }
    dtimg=true,bin=false,inputimg=false,cclimg=false,fdtimg=false,hg=false;
    drawimage();
}
void MainWindow::on_histogram_equilization_clicked()
{
    int intensity[256],index,i,j,k,max=-1;
    double normal[256];
    for(i=0;i<256;i++)intensity[i]=0;
    if(hg==true)
    {
        for(k=0;k<Zdim;k++)
        {
            for(j=0;j<Ydim;j++)
            {
                for(i=0;i<Xdim;i++)
                {
                    index=a[i][j][k];
                    intensity[index]=intensity[index]+1;
                    if(index>max)max=index;
                }
            }
        }
        printf("Maxdt=%d",max);
      /*  for(i=1;i<256;i++)//cummulative sum
        {
            intensity[i]=intensity[i]+intensity[i-1];
            normal[i]=(double)(intensity[i]/(double)(Xdim*Ydim*Zdim))*255;
        }
        for(k=0;k<Zdim;k++)
        {
            for(j=0;j<Ydim;j++)
            {
                for(i=0;i<Xdim;i++)
                {
                    index=a[i][j][k];
                    hist[i][j][k]=normal[index];
                }
            }
        }
        hg=true;inputimg=false;dtimg=false;cclimg=false,bin=false,fdtimg=false;
        drawimage();*/
    }
}

void MainWindow::on_ccl_clicked()
{
    int i,j,k,p,q,temp1,c,c1,curlabel=1,nz,neighbor[13];
    int min;
    struct node *curnode,*temp,*ar[3000];
    cc=0;
    for(i=2;i<12;i++)component[i]=0;
    for(i=0;i<3000;i++)
    {
        ar[i]=(struct node *)malloc(sizeof(struct node));
        ar[i]->data=i;
        ar[i]->next=NULL;
    }
    for(k=0;k<Zdim;k++)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
                if(ipimg[i][j][k]!=0)ccl[i][j][k]=1;
                else
                    ccl[i][j][k]=0;
            }
        }
    }
    //First pass
    for(k=0;k<Zdim;k++)
        {
            for(j=0;j<Ydim;j++)
            {
                for(i=0;i<Xdim;i++)
                {
                    if(ipimg[i][j][k]!=0)
                    {
                        nz=0;
                        for(c=0;c<13;c++)neighbor[c]=0;
                        if(i-1>=0&&ccl[i-1][j][k]>1)
                        {
                            neighbor[0]=ccl[i-1][j][k];
                            nz++;
                        }
                        else if(i-1>=0&&j-1>=0&&ccl[i-1][j-1][k]>1)
                        {
                            neighbor[1]=ccl[i-1][j-1][k];
                            nz++;
                        }
                        else if(j-1>=0&&ccl[i][j-1][k]>1)
                        {
                            neighbor[2]=ccl[i][j-1][k];
                            nz++;
                        }
                        else if(i+1<Xdim&&j-1>=0&&ccl[i+1][j-1][k]>1)
                        {
                            neighbor[3]=ccl[i+1][j-1][k];
                            nz++;
                        }
                        else if(k-1>=0&&ccl[i][j][k-1]>1)
                        {
                            neighbor[4]=ccl[i][j][k-1];
                            nz++;
                        }
                        else if(i-1>=0&&k-1>=0&&ccl[i-1][j][k-1]>1)
                        {
                            neighbor[5]=ccl[i-1][j][k-1];
                            nz++;
                        }
                        else if(i+1<Xdim&&k-1>=0&&ccl[i+1][j][k-1]>1)
                        {
                            neighbor[6]=ccl[i+1][j][k-1];
                            nz++;
                        }
                        else if(k-1>=0&&j-1>=0&&ccl[i][j-1][k-1]>1)
                        {
                            neighbor[7]=ccl[i][j-1][k-1];
                            nz++;
                        }
                        else  if(k-1>=0&&j+1<Ydim&&ccl[i][j+1][k-1]>1)
                        {
                            neighbor[8]=ccl[i][j+1][k-1];
                            nz++;
                        }
                        else if(k-1>=0&&i-1>=0&&j-1>=0&&ccl[i-1][j-1][k-1]>1)
                        {
                            neighbor[9]=ccl[i-1][j-1][k-1];
                            nz++;
                        }
                        else if(k-1>=0&&i+1<Xdim&&j-1>=0&&ccl[i+1][j-1][k-1]>1)
                        {
                            neighbor[10]=ccl[i+1][j-1][k-1];
                            nz++;
                        }
                        else if(k-1>=0&&i-1>=0&&j+1<Ydim&&ccl[i-1][j+1][k-1]>1)
                        {
                            neighbor[11]=ccl[i-1][j+1][k-1];
                            nz++;
                        }
                        else if(k-1>=0&&i+1<Xdim&&j+1<Ydim&&ccl[i+1][j+1][k-1]>1)
                        {
                            neighbor[12]=ccl[i+1][j+1][k-1];
                            nz++;
                        }
                        /*else
                        {}*/

                        if(nz==0)
                        {
                            curlabel++;
                            ccl[i][j][k]=curlabel;
                        }
                        else
                        {
                            for(p=0;p<13;p++)
                            {
                                min=p;
                                for(q=p+1;q<13;q++)
                                {
                                    if(neighbor[q]<neighbor[min])min=q;
                                }
                                temp1=neighbor[p];
                                neighbor[p]=neighbor[min];
                                neighbor[min]=temp1;
                            }
                            for(c=0;c<13;c++)
                            {
                                if(neighbor[c]>1)
                                {
                                    min=neighbor[c];
                                    break;
                                }
                            }
                            ccl[i][j][k]=min;
                            curnode=(struct node *)malloc(sizeof(struct node));
                            for(c1=c+1;c1<13;c1++)
                            {
                                temp=ar[min];
                                curnode=(struct node *)malloc(sizeof(struct node));
                                curnode->data=neighbor[c1];
                                curnode->next=NULL;
                                if(temp->next==NULL)
                                {
                                    temp->next=curnode;
                                }
                                else
                                {
                                    curnode->next=temp->next;
                                    temp->next=curnode;
                                }
                                curnode=NULL;
                                temp=NULL;
                                free(temp);
                                free(curnode);
                            }
                        }
                    }
                }
            }
        }
        //Second pass
    for(i=2;i<3000;i++)
    {
        temp=ar[i];
        while(temp->next!=NULL)
        {
            temp=temp->next;
            ar[temp->data]->data=ar[i]->data;
        }
    }

    for(k=0;k<Zdim;k++)
    {
        for(j=0;j<Ydim;j++)
        {
            for(i=0;i<Xdim;i++)
            {
               ccl[i][j][k]=ar[ccl[i][j][k]]->data;
               component[ccl[i][j][k]]=component[ccl[i][j][k]]+1;
            }
        }
    }
    for(i=2;i<12;i++)
    {
        if(component[i]!=0)
        {
            cc++;
        }
    }
    ui->nocc->setNum(cc);
    inputimg=false, dtimg=false, cclimg=true,fdtimg=false,bin=false,hg=false;
    drawimage();
}


