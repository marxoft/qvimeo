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

#ifndef URLS_H
#define URLS_H

#include <QString>

namespace QVimeo {

// API
static const QString API_URL("https://api.vimeo.com");

// Authentication
static const QString AUTH_URL("https://api.vimeo.com/oauth/authorize");
static const QString CLIENT_AUTH_URL("https://api.vimeo.com/oauth/authorize/client");
static const QString TOKEN_URL("https://api.vimeo.com/oauth/access_token");

static const QString GRANT_TYPE_CODE("authorization_code");
static const QString GRANT_TYPE_CLIENT("client_credentials");

static const QString PUBLIC_SCOPE("public");
static const QString PRIVATE_SCOPE("private");
static const QString PURCHASED_SCOPE("purchased");
static const QString CREATE_SCOPE("create");
static const QString EDIT_SCOPE("edit");
static const QString DELETE_SCOPE("delete");
static const QString INTERACT_SCOPE("interact");
static const QString UPLOAD_SCOPE("upload");

// VideoPage
static const QString VIDEO_PAGE_URL("http://player.vimeo.com/video");

}

#endif // URLS_H
