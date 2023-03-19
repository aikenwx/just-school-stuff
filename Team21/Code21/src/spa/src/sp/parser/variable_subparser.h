#pragma once

#include "subparser.h"

namespace parser {
class VariableSubparser : public Subparser {
public:
  bool Parse(std::shared_ptr<Context> context) override;
};
}  // namespace parser
