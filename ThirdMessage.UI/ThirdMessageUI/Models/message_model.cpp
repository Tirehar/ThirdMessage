#include "message_model.h"

#include <utility>

MessageModel::MessageModel(QString otherId, bool isMy, QString content, int time) : otherId(std::move(otherId)), isMy(isMy), content(std::move(content)), time(time) {}
