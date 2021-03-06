// Author: vividfree (vividfree@qq.com)
//  Date : 2015-12-30
// Note : sample.label_id_ 只能取 0 (kNegativeLabelID) 或者
//        1 (kPositiveLabelID)，且1为正类别

#ifndef MACHINE_LEARNING_SRC_MODEL_LR_MODEL_H_
#define MACHINE_LEARNING_SRC_MODEL_LR_MODEL_H_

#include "machine_learning/src/model/supervised_model.h"

namespace machine_learning {

namespace data_dict {
class ArrayParamValueDict;
}  // namespace data_dict

namespace supervised_model {

class LRModel : public SupervisedModel {
 public:
  static const int kPositiveLabelID;
  static const int kNegativeLabelID;
  static const float kPositiveThreshold;

  explicit LRModel(const data_dict::ArrayParamValueDict& data_reader);
  virtual ~LRModel();

  bool Init();

  // 计算模型预测的分数
  // NOTE: 不会用到sample.weight_ 和 sample.label_id_
  virtual bool ModelFunction(const util::SampleWithLabel& sample,
                             float* model_score) const;

  // 计算loss
  // NOTE 1: loss_score是取log后的损失值 (这句话暂时没出现在 SupervisedModel 中)
  // NOTE 2: 会用到sample.weight_ 和 sample.label_id_
  virtual bool LossFunction(const util::SampleWithLabel& sample,
                            float* loss_score) const;

  // 计算gradient
  // NOTE: 会用到sample.weight_ 和 sample.label_id_
  virtual bool GradientFunction(const util::SampleWithLabel& sample,
                                std::map<int, float>* gradient) const;

  // 基于模型预测的分数，给出预测的label_id
  // NOTE: 不会用到sample.weight_ 和 sample.label_id_
  virtual bool Predict(const util::SampleWithLabel& sample,
                       int* max_score_label_id,
                       std::map<int, float>* label_score) const;

  bool Destroy();

 private:
  const data_dict::ArrayParamValueDict* data_reader_;
};

}  // namespace supervised_model
}  // namespace machine_learning

#endif  // MACHINE_LEARNING_SRC_MODEL_LR_MODEL_H_
