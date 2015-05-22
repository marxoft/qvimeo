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

#include "streamsrequest.h"
#include "request_p.h"
#include "urls.h"
#include <QNetworkReply>

namespace QVimeo {

class Format : public QVariantMap
{

public:
    Format() :
        QVariantMap()
    {
    }
    
    Format(const QString &id, const QString &desc, const QString &ext, int width, int height) :
        QVariantMap()
    {
        insert("id", id);
        insert("description", desc);
        insert("ext", ext);
        insert("width", width);
        insert("height", height);
    }
};

class FormatHash : public QHash<QString, Format>
{

public:
    FormatHash() : 
        QHash<QString, Format>() 
    {
        insert("mobile", Format("mobile", "H264 audio/video", "mp4", 480, 270));
        insert("sd", Format("sd", "H264 audio/video", "mp4", 640, 352));
        insert("hd", Format("hd", "H264 audio/video", "mp4", 1280/1920, 720/1080));
    }
};

class StreamsRequestPrivate : public RequestPrivate
{

public:
    StreamsRequestPrivate(StreamsRequest *parent) :
        RequestPrivate(parent)
    {
    }
    
    void _q_onReplyFinished() {
        if (!reply) {
            return;
        }
    
        Q_Q(StreamsRequest);
        
        switch (reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            setStatus(Request::Canceled);
            setError(Request::NoError);
            setErrorString(QString());
            emit q->finished();
            return;
        default:
            setStatus(Request::Failed);
            setError(Request::Error(reply->error()));
            setErrorString(reply->errorString());
            emit q->finished();
            return;
        }
        
        bool ok;
        QVariantMap info = QtJson::Json::parse(QString(reply->readAll()).section("\"h264\":", 1, 1)
                                                                        .section(",\"hls\":", 0, 0), ok).toMap();
        
        if (ok) {
            QVariantList list;
            QHashIterator<QString, Format> iterator(formatHash);
            
            while (iterator.hasNext()) {
                iterator.next();
                QVariant v = info.value(iterator.key());
                
                if (!v.isNull()) {
                    QVariantMap m = v.toMap();
                    Format format = iterator.value();
                    format["url"] = m.value("url");
                    format["width"] = m.value("width");
                    format["height"] = m.value("height");
                    list << format;
                }
            }
            
            setResult(list);
            setStatus(Request::Ready);
            setError(Request::NoError);
            setErrorString(QString());
        }
        else {
            setStatus(Request::Failed);
            setError(Request::ParseError);
            setErrorString(Request::tr("Unable to parse response"));
        }

        emit q->finished();
    }        
    
    static FormatHash formatHash;
                
    Q_DECLARE_PUBLIC(StreamsRequest)
};

FormatHash StreamsRequestPrivate::formatHash;

/*!
    \class StreamsRequest
    \brief Handles requests for video streams
    
    \ingroup requests
    
    The StreamsRequest class is used for requesting a list of streams for a Vimeo video.
    
    Example usage:
    
    C++
    
    \code
    using namespace QVimeo;
    
    ...
    
    StreamsRequest request;
    request.list(VIDEO_ID);
    connect(&request, SIGNAL(finished()), this, SLOT(onRequestFinished()));
    
    ...
    
    void MyClass::onRequestFinished() {
        if (request.status() == StreamsRequest::Ready) {
            foreach (QVariant stream, request.result().toList()) {
                qDebug() << "ID:" << stream.value("id").toString();
                qDebug() << "Description:" << stream.value("description").toString();
                qDebug() << "Extension:" << stream.value("ext").toString();
                qDebug() << "Width:" << stream.value("width").toInt();
                qDebug() << "Height:" << stream.value("height").toInt();
                qDebug() << "URL:" << stream.value("url").toString();
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
    
    StreamsRequest {
        id: request
        
        onFinished: {
            if (status == StreamsRequest.Ready) {
                for (var i = 0; i < result.length; i++) {
                    console.log("ID: " + result[i].id);
                    console.log("Description: " + result[i].description);
                    console.log("Extension: " + result[i].ext);
                    console.log("Width: " + result[i].width);
                    console.log("Height: " + result[i].height);
                    console.log("URL: " + result[i].url);
                }
            }
            else {
                console.log(errorString);
            }
        }
        
        Component.onCompleted: list(VIDEO_ID)
    }
    \endcode
*/
StreamsRequest::StreamsRequest(QObject *parent) :
    Request(*new StreamsRequestPrivate(this), parent)
{
}

/*!
    \brief Requests a list of streams for the video identified by id.
*/
void StreamsRequest::list(const QString &id) {    
    setUrl(VIDEO_PAGE_URL + "/" + id);
    get(false);
}

}

#include "moc_streamsrequest.cpp"
