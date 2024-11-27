#ifndef TEXTATTACHMENTTYPE_H
#define TEXTATTACHMENTTYPE_H

namespace DWG
{
namespace Common
{

/**
 * @enum TextAttachmentType
 * @brief Enumeration for text attachment types.
 * @remarks
 * Values 0-8 are used for the left/right attachment points (attachment
 * direction is horizontal),
 * values 9-10 are used for the top/bottom attachment points (attachment
 * direction is vertical).
 */
enum TextAttachmentType : short
{
  /**
   * @brief Top of top text line.
   */
  TopOfTopLine = 0,

  /**
   * @brief Middle of top text line.
   */
  MiddleOfTopLine = 1,

  /**
   * @brief Middle of text.
   */
  MiddleOfText = 2,

  /**
   * @brief Middle of bottom text line.
   */
  MiddleOfBottomLine = 3,

  /**
   * @brief Bottom of bottom text line.
   */
  BottomOfBottomLine = 4,

  /**
   * @brief Bottom text line.
   */
  BottomLine = 5,

  /**
   * @brief Bottom of top text line. Underline bottom line.
   */
  BottomOfTopLineUnderlineBottomLine = 6,

  /**
   * @brief Bottom of top text line. Underline top line.
   */
  BottomOfTopLineUnderlineTopLine = 7,

  /**
   * @brief Bottom of top text line. Underline all content.
   */
  BottomofTopLineUnderlineAll = 8,

  /**
   * @brief Center of text (y-coordinate only).
   */
  CenterOfText = 9,

  /**
   * @brief Center of text (y-coordinate only), and overline top/underline
   * bottom content.
   */
  CenterOfTextOverline = 10,
};

} // namespace Common
} // namespace DWG

#endif /* TEXTATTACHMENTTYPE_H */