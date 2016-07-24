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
        
        const QString response = reply->readAll();
        const QNetworkReply::NetworkError e = reply->error();
        const QString es = reply->errorString();
        reply->deleteLater();
        reply = 0;
        
        switch (e) {
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
            setError(Request::Error(e));
            setErrorString(es);
            emit q->finished();
            return;
        }
        
        bool ok;
        const QVariantList formats = QtJson::Json::parse(response.section("\"progressive\":", 1, 1)
                                                                 .section("]", 0, 0) + "]", ok).toList();
        
        if (ok) {
            QVariantList list;
            
            foreach (const QVariant &v, formats) {
                const QVariantMap f = v.toMap();
                QVariantMap format;
                format["description"] = f.value("mime");
                format["ext"] = "mp4";
                format["id"] = f.value("quality");
                format["url"] = f.value("url").toString().replace("https://", "http://");
                format["width"] = f.value("width");
                format["height"] = f.value("height");
                list << format;
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
                    
    Q_DECLARE_PUBLIC(StreamsRequest)
};

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
    if (status() == Loading) {
        return;
    }
    
    setUrl(VIDEO_PAGE_URL + "/" + id);
    get(false);
}

}

#include "moc_streamsrequest.cpp"
