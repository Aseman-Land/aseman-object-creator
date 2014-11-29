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

#ifndef OBJECTCREATOR_H
#define OBJECTCREATOR_H

#include <QString>

class ObjectCreator
{
public:
    ObjectCreator();

    QString createObject(const QString & data);
    QString extractIncludes(const QString & data);
    QString extractClasses(const QString & data);
    QString extractInitializes(const QString & data);
    QString extractClassBody(const QString & clssName, const QString & body);
    QString extractClassProperties(const QString & clssName, const QString & body);
    QString extractClassSignals(const QString & clssName, const QString & body);
    QString extractClassVariables(const QString & clssName, const QString & body);
    QString extractClassDefaults(const QString & clssName, const QString & body);
    QString extractClassEquals(const QString & clssName, const QString & body);

    void setFileTemplate( const QString & path );
    void setClassTemplate( const QString & path );
    void setInitlalizeTemplate( const QString & path );
    void setBodyReadTemplate( const QString & path );
    void setBodyWriteTemplate( const QString & path );
    void setBodyNotifyTemplate( const QString & path );
    void setPropertyReadTemplate( const QString & path );
    void setPropertyWriteTemplate( const QString & path );
    void setVariablesTemplate( const QString & path );
    void setDefaultsTemplate( const QString & path );
    void setEqualsTemplate( const QString & path );

private:
    QString file_template;
    QString class_template;
    QString initialize_template;
    QString body_read_template;
    QString body_write_template;
    QString body_notify_template;
    QString property_read_template;
    QString property_write_template;
    QString variables_template;
    QString defaults_template;
    QString equals_template;
};

#endif // OBJECTCREATOR_H
