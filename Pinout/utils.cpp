#include "utils.h"

/*
 * Util.cpp  Created on: 11 May 2015
 * Copyright (c) 2015 Derek Molloy (www.derekmolloy.ie)
 * Made available for the book "Exploring Raspberry Pi"
 * See: www.exploringrpi.com
 * Licensed under the EUPL V.1.1
 *
 * This Software is provided to You under the terms of the European
 * Union Public License (the "EUPL") version 1.1 as published by the
 * European Union. Any use of this Software, other than as authorized
 * under this License is strictly prohibited (to the extent such use
 * is covered by a right of the copyright holder of this Software).
 *
 * This Software is provided under the License on an "AS IS" basis and
 * without warranties of any kind concerning the Software, including
 * without limitation merchantability, fitness for a particular purpose,
 * absence of defects or errors, accuracy, and non-infringement of
 * intellectual property rights other than copyright. This disclaimer
 * of warranty is an essential part of the License and a condition for
 * the grant of any rights to this Software.
 *
 * For more details, see http://www.derekmolloy.ie/
 */

#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDebug>
using namespace std;

namespace exploringRPi {

    /**
     * Helper write function that writes a single string value to a file in the path provided
     * @param path The sysfs path of the file to be modified
     * @param filename The file to be written to in that path
     * @param value The value to be written to the file
     * @return
     */
    int write(string path, string filename, string value){
       ofstream fs;
       fs.open((path + filename).c_str());
       //qDebug()<<(path + filename).c_str()<<" "<<value.c_str();
       if (!fs.is_open()){
           qDebug()<<"GPIO/PWM: write failed to open file "<<(path + filename).c_str();
           return -1;
       }
       fs << value;
       fs.close();
       return 0;
    }
    /**
     * Helper read function that reads a single string value to a file from the path provided
     * @param path The sysfs path of the file to be read
     * @param filename Filename The file to be written to in that path
     * @return
     */
    string read(string path, string filename){
       ifstream fs;
       fs.open((path + filename).c_str());
       if (!fs.is_open()){
           qDebug()<<"GPIO/PWM: read failed to open file "<<(path + filename).c_str();
        }
       string input;
       getline(fs,input);
       fs.close();
       return input;
    }

    /**
     * Private write method that writes a single int value to a file in the path provided
     * @param path The sysfs path of the file to be modified
     * @param filename The file to be written to in that path
     * @param value The int value to be written to the file
     * @return
     */
    int write(string path, string filename, int value){
       stringstream s;
       s << value;
       return write(path,filename,s.str());
    }

} /* namespace exploringRPi */
