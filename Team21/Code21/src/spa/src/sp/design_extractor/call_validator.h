#pragma once

#include "extractor.h"

namespace design_extractor {
class CallValidator : public Extractor {
public:
  CallValidator() = default;
  void HandleCallNode(const std::shared_ptr<ast::CallNode>& node,
    int depth) override;
  void HandleProgramNode(const std::shared_ptr<ast::ProgramNode>& node,
    int depth) override;

private:
  std::shared_ptr<ast::ProgramNode> program;
};
}  // namespace design_extractor
