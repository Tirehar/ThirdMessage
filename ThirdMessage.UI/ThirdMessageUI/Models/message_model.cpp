#include "message_model.h"

#include <utility>

MessageModel::MessageModel(int otherId, bool isMy, QString content, int time) : otherId(otherId), isMy(isMy), content(std::move(content)), time(time) {}
