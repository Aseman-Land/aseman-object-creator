/*
    Copyright (C) 2014 Aseman
    http://aseman.co

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define FIX_PATH( PATH_VAR, VALUE ) \
    QString PATH_VAR = VALUE; \
    if( PATH_VAR.mid(0,1) != "/" ) \
        PATH_VAR = QDir::currentPath() + "/" + PATH_VAR; \

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QStringList>
#include <QDebug>
#include <QSet>

#include "objectcreator.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    const QStringList & args = app.arguments();

    QString src = "/home/bardia/stickers.vco";
    QString dst = "/home/bardia/stickers.h";

    QSet<QString> twice_checker;
    ObjectCreator creator;
    for( int i=1; i<args.count(); i++ )
    {
        const QStringList & split = args.at(i).split("=");
        if( split.count() != 2 )
        {
            qWarning() << "Bad input: " + args.at(i);
            return 0;
        }

        const QString & var = split.at(0);
        const QString & val = split.at(1);
        FIX_PATH(path, val);

        if( twice_checker.contains(var) )
        {
            qWarning() << "Twice: " + var;
            return 0;
        }
        else
            twice_checker.insert(var);

        if( var == "if" )
            src = path;
        else
        if( var == "of" )
            dst = path;
        else
        if( var == "template_file" )
            creator.setFileTemplate(path);
        else
        if( var == "template_class" )
            creator.setClassTemplate(path);
        else
        if( var == "template_initialize" )
            creator.setInitlalizeTemplate(path);
        else
        if( var == "template_body_write" )
            creator.setBodyWriteTemplate(path);
        else
        if( var == "template_body_read" )
            creator.setBodyReadTemplate(path);
        else
        if( var == "template_body_notify" )
            creator.setBodyNotifyTemplate(path);
        else
        if( var == "template_presets" )
            creator.setDefaultsTemplate(path);
        else
        if( var == "template_equals" )
            creator.setEqualsTemplate(path);
        else
        if( var == "template_variables" )
            creator.setVariablesTemplate(path);
        else
        if( var == "template_property_ro" )
            creator.setPropertyReadTemplate(path);
        else
        if( var == "template_property_rw" )
            creator.setPropertyWriteTemplate(path);
        else
        {
            qWarning() << "Bad input: " + args.at(i);
            return 0;
        }
    }

    if( src.isEmpty() )
    {
        qWarning() << "Input is empty: if=path";
        return 0;
    }
    if( dst.isEmpty() )
    {
        qWarning() << "Outpyt is empty: of=path";
        return 0;
    }

    QFile srcFile(src);
    if( !srcFile.open(QFile::ReadOnly) )
    {
        qWarning() << "Can't open input file";
        return 0;
    }

    const QString & data = creator.createObject(srcFile.readAll());
    srcFile.close();

    QFile dstFile(dst);
    if( !dstFile.open(QFile::WriteOnly) )
    {
        qWarning() << "Can't open output file";
        return 0;
    }

    dstFile.write(data.toUtf8());
    dstFile.flush();
    dstFile.close();
    return 0;
}
