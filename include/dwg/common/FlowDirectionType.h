#ifndef FLOWDIRECTIONTYPE_H
#define FLOWDIRECTIONTYPE_H

namespace DWG
{
namespace Common
{

enum FlowDirectionType : short
{
  Horizontal = 1,
  Vertical   = 3,
  ByStyle    = 6,
};

} // namespace Common
} // namespace DWG

#endif /* FLOWDIRECTIONTYPE_H */