#pragma once

#include "subparser.h"

namespace parser {
class IfSubparser : public Subparser {
public:
  bool Parse(std::shared_ptr<Context> context) override;
};
}  // namespace parser
