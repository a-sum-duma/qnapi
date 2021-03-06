/*****************************************************************************
** QNapi
** Copyright (C) 2008-2017 Piotr Krzemiński <pio.krzeminski@gmail.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
*****************************************************************************/

#ifndef SUBTITLE_MATCHER_H
#define SUBTITLE_MATCHER_H

#include "subtitlelanguage.h"
#include "subconvert/subtitleformatsregistry.h"

#include <QFileInfo>
#include <QSharedPointer>

class SubtitleMatcher : public QObject {
  Q_OBJECT
 public:
  SubtitleMatcher(bool _noBackup, LangCodeType _langCodeInFileName,
                  bool _isPostProcessingEnabled, QString _ppSubFormat,
                  QString _ppSubExtension, bool _changePermissions,
                  QString _changePermissionsTo,
                  const QSharedPointer<const SubtitleFormatsRegistry>
                      &subtitleFormatsRegistry);

  /* TODO: Fill in versions. */
  /**
   * @deprecated Since X.X.X. Will be removed in X.X.X.
   *             Use constructor that accepts #LangCodeType.
   */
  Q_DECL_DEPRECATED
  SubtitleMatcher(bool _noBackup, bool _isPostProcessingEnabled,
                  QString _ppSubFormat, QString _ppSubExtension,
                  bool _changePermissions, QString _changePermissionsTo,
                  const QSharedPointer<const SubtitleFormatsRegistry>
                      &subtitleFormatsRegistry)
      : SubtitleMatcher(_noBackup, LCT_NONE, _isPostProcessingEnabled,
                        _ppSubFormat, _ppSubExtension, _changePermissions,
                        _changePermissionsTo, subtitleFormatsRegistry) {}

  bool matchSubtitles(QString subtitlesTmpFilePath,
                      QString targetMovieFilePath,
                      QString subtitlesLanguage = QString()) const;

 private:
  QString selectTargetExtension(QFileInfo subtitlesTmpFileInfo) const;
  QString constructSubtitlePath(QString targetMovieFilePath,
                                QString targetExtension,
                                QString subtitlesLanguage,
                                QString baseSuffix = "") const;
  bool isWritablePath(QString path) const;
  void removeOrCopy(QString targetMoviefilePath,
                    QString targetSubtitlesFilePath,
                    QString subtitlesLanguage) const;
  bool dryCopy(QString srcFilePath, QString dstFilePath) const;
  void fixFilePermissions(QString targetSubtitlesFilePath,
                          QString changePermissionsTo) const;

  bool noBackup;
  LangCodeType langCodeInFileName;
  bool isPostProcessingEnabled;
  QString ppSubFormat;
  QString ppSubExtension;
  bool changePermissions;
  QString changePermissionsTo;

  QSharedPointer<const SubtitleFormatsRegistry> subtitleFormatsRegistry;
};

#endif  // SUBTITLE_MATCHER_H
