/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "resourcesrequest.h"
#include "request_p.h"
#include "urls.h"

namespace QVimeo {

/*!
    \class ResourcesRequest
    \brief Handles requests for Vimeo resources.
    
    \ingroup requests
    
    The ResourcesRequest class is used for making requests to the Vimeo Data API that concern 
    Vimeo resources.
    
    Example usage:
    
    C++
    
    \code
    using namespace QVimeo;
    
    ...
    
    ResourcesRequest request;
    request.get("/videos/VIDEO_ID");
    connect(&request, SIGNAL(finished()), this, SLOT(onRequestFinished()));
    
    ...
    
    void MyClass::onRequestFinished() {
        if (request.status() == ResourcesRequest::Ready) {            
            QMapIterator<QString, QVariant> iterator(request.result().toMap());
            
            while (iterator.hasNext()) {
                iterator.next();
                qDebug() << iterator.key() << "=" << iterator.value();
            }
        }
        else {
            qDebug() << request.errorString();
        }
    }
    \endcode
    
    QML
    
    \code
    import QtQuick 1.0
    import QVimeo 1.0
    
    ResourcesRequest {
        id: request

        onFinished: {
            if (status == ResourcesRequest.Ready) {
                for (var k in result) {
                    console.log(att + " = " + result[k]);
                }
            }
            else {
                console.log(errorString);
            }
        }
        
        Component.onCompleted: get("/videos/VIDEO_ID")
    }
    \endcode
    
    For more details about Vimeo resources, see the Vimeo reference documentation 
    <a target="_blank" href="https://developer.vimeo.com/api/endpoints/resources">here</a>.
*/
ResourcesRequest::ResourcesRequest(QObject *parent) :
    Request(parent)
{
}

/*!
    \brief Requests a list of Vimeo resources from \a resourcePath.
    
    For example, to search videos:
    
    \code
    ResourcesRequest request;
    QVariantMap filters;
    filters["per_page"] = 10;
    filters["sort"] = "date";
    filters["query"] = "Qt";
    request.list("/videos", filters);
    \endcode
*/
void ResourcesRequest::list(const QString &resourcePath, const QVariantMap &filters) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
#if QT_VERSION >= 0x050000    
    if (!filters.isEmpty()) {
        QUrlQuery query(u);
        addUrlQueryItems(&query, filters);
        u.setQuery(query);
    }
#else    
    if (!filters.isEmpty()) {
        addUrlQueryItems(&u, filters);
    }
#endif
    setUrl(u);
    Request::get();
}

/*!
    \brief Retrieves the Vimeo resource from \a resourcePath.
    
    For example, to retrieve a video:
    
    \code
    ResourcesRequest request;
    request.get("/videos/VIDEO_ID");
    \endcode
*/
void ResourcesRequest::get(const QString &resourcePath) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
    setUrl(u);
    Request::get();
}

/*!
    \brief Inserts a Vimeo resource into \a resourcePath using a PUT request.
    
    For example, to 'like' a video on behalf of the authenticated user:
    
    \code
    ResourcesRequest request;
    request.insert("/me/likes/VIDEO_ID");
    \endcode
*/
void ResourcesRequest::insert(const QString &resourcePath) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
    setUrl(u);
    Request::put();
}

/*!
    \brief Inserts a new Vimeo resource.
    
    For example, to insert a new album on behalf of the authenticated user:
    
    \code
    ResourcesRequest request;
    QVariantMap album;
    album["name"] = "My album";
    album["description"] = "Album inserted using QVimeo";
    album["privacy"] = "anybody";
    album["sort"] = "newest";
    request.insert(album, "/me/albums");
    \endcode
*/
void ResourcesRequest::insert(const QVariantMap &resource, const QString &resourcePath) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
    QString body;
    addPostBody(&body, resource);
    setUrl(u);
    setData(body);
    post();
}

/*!
    \brief Updates the Vimeo resource at \a resourcePath.
    
    For example, to update an existing album on behalf of the authenticated user:
    
    \code
    ResourcesRequest request;
    QVariantMap album;
    album["name"] = "My new album name";
    album["description"] = "My new album description";
    request.update("/me/albums/ALBUM_ID", album);
    \endcode
*/
void ResourcesRequest::update(const QString &resourcePath, const QVariantMap &resource) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
    QString body;
    addPostBody(&body, resource);
    setUrl(u);
    setData(body);
    patch();
}

/*!
    \brief Deletes the Vimeo resource at \a resourcePath.
    
    For example, to 'unlike' a video on behalf of the authenticated user:
    
    \code
    ResourcesRequest request;
    request.del("/me/likes/VIDEO_ID");
    \endcode
*/
void ResourcesRequest::del(const QString &resourcePath) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
    setUrl(u);
    deleteResource();
}

}