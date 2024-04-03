/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * www.rt-labs.com
 * Copyright 2021 rt-labs AB, Sweden.
 *
 * This software is licensed under the terms of the BSD 3-clause
 * license. See the file LICENSE distributed with this software for
 * full license information.
 ********************************************************************/

#include "osal_log.h"

#include <cstdarg>
#include <cstdio>

#include "logger.hpp"
#include "string_format.hpp"

void os_log (uint8_t type, const char * fmt, ...)
{
   using bestsens::Logger;
   va_list list;

   va_start (list, fmt);
   const auto finished_msg = stringFormat (std::string_view{fmt}, list);
   va_end (list);

   switch (LOG_LEVEL_GET (type))
   {
   case LOG_LEVEL_DEBUG:
      return Logger::log_detail<Logger::level::debug> (finished_msg);
   case LOG_LEVEL_INFO:
      return Logger::log_detail<Logger::level::info> (finished_msg);
   case LOG_LEVEL_WARNING:
      return Logger::log_detail<Logger::level::warn> (finished_msg);
   case LOG_LEVEL_ERROR:
      return Logger::log_detail<Logger::level::err> (finished_msg);
   case LOG_LEVEL_FATAL:
      return Logger::log_detail<Logger::level::critical> (finished_msg);
   default:
      return Logger::log_detail<Logger::level::info> (finished_msg);
   }
}
