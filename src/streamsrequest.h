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

#ifndef QVIMEO_STREAMSREQUEST_H
#define QVIMEO_STREAMSREQUEST_H

#include "request.h"

namespace QVimeo {

class StreamsRequestPrivate;

class QVIMEOSHARED_EXPORT StreamsRequest : public Request
{
    Q_OBJECT
    
public:
    explicit StreamsRequest(QObject *parent = 0);

public Q_SLOTS:
    void list(const QString &id);
    
private:    
    Q_DECLARE_PRIVATE(StreamsRequest)
    Q_DISABLE_COPY(StreamsRequest)
};

}

#endif // QVIMEO_STREAMSREQUEST_H
