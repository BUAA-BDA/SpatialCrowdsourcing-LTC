SpatialCrowdsourcing-LTC: Latency-oriented Task Completion via Spatial Crowdsourcing
========================================================================

This repository stores the source code of the proposed solutions to the problem called LTC in the following paper.

[1] **Latency-Oriented Task Completion via Spatial Crowdsourcing.**
*Yuxiang Zeng, Yongxin Tong, Lei Chen, Zimu Zhou.* ICDE 2018: 317-328. [link](https://doi.org/10.1109/ICDE.2018.00037) [slides](http://yongxintong.group/static/paper/2018/ICDE18_Latency-oriented%20Task%20Completion%20via%20Spatial%20Crowdsourcing-slides.pptx)

If you find this work helpful in your research, please consider citing our paper and the bibtex are listed below:
```  
@inproceedings{DBLP:conf/icde/ZengTCZ18,
  author    = {Yuxiang Zeng and
               Yongxin Tong and
               Lei Chen and
               Zimu Zhou},
  title     = {Latency-Oriented Task Completion via Spatial Crowdsourcing},
  booktitle = {{ICDE}},
  pages     = {317--328},
  year      = {2018},
}
```  



Usage of the algorithms
---------------

### Environment

gcc/g++ version: 7.4.0 

OS: Ubuntu

### Compile the algorithms

cd algorithm && make all

LAF: the LAF algorithm in the paper

AAM: the AAM algorithm in the paper

### Run the algorithms

./LAF ../dataset/synthetic/1000_6_0.14_30_0.86_N/data_00.txt

1000_6_0.14_30_0.86_N: the varied parameters

data_00.txt: the information of the tasks and workers (i.e., the input)

Description of the data generator
---------------

### Environment

Python: 2.7

### Run the scripts

genDataSynthetic.py: a script to generate the synthetic datasets in the experiments

synthetic: a sample of the synthetic datasets


Related other resources
------------------------
We have maintained a paper list of the studies on spatial crowdsourcing. [link](https://github.com/BUAA-BDA/SpatialCrowdsourcing-Survey)


Contact
------------
- Yuxiang Zeng: yzengal@cse.ust.hk
- Yongxin Tong: yxtong@buaa.edu.cn

