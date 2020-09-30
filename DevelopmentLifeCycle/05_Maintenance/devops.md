

### Virtual Machine

* �a�V�X�R: �z�L�[�jCPU�BMemory�BDisk���覡�A�����귽�X�R�C(�h�ӪA�ȩ�b�P�@�x������)

* ��V�X�R: �W�[�������ƶq�C(�h�ӪA�ȩ�b�P�@�x�������A�P�ɦ��ƴ�����)

* �L�A�ȮɥN (�@�ӪA�ȩ�@�x�������A�B�P�ɤ]�㦳�ƴ�����)
    * ���O�������
    * ������
    * �޲z���K
    * �����ɯŤ��e��
    
### �e����

#### �w�ѨM���D    
    * �ɯŮe���A���ҳ��: (Docker �A�ȴN�O���Ҧb�������ҧֳt�G�p)(�u�ݭn��ӡu�M����(image)�v�����A�Y�i���������ɯšC)
    * �A�ȧG�p�ֳt: docker-compose.yml + ���O
    * �޲z��K

#### ���ѨM���D
    * ���O�����귽: �A�ȥD�n�٬O�z�L�u�������v�i�湺��, �ݭn���h�x������
    * ������: �o�ʶR�������u������v�ƶq�A�קK�u�������v�ƶq�L�h�A���m�u������v�귽�C
    
#### �M�D����
    * �Τu��޲z�e�j�ƶq�� container�C(ex: docker swarm�BK8S�BK3S...)
    * �ϥζ���Server
    * �b�귽�������������p�A�|��ĳ�H�u������v���N�u�������v, ���ΦA��귽�b���Ѿ���OS�ϥ�
    
### docker command vs docker-compose 

#### �u�ϥ�docker command ���O�ظm�����I
    * �L�k�i�檩������
    * �C��s���ҩΪ̷s�����ݭn�ۦP�A�ȮɡA����������ۦP���O�A�e���ƶq�V�h�ɴN�V���H����C
    * ��������`�ɡA�S����k���t�N�A�ȫظm����
    * �ҥH __��ĳ�z�L docker-compose.yml �ɮװ��������O�d__
    * �C�@���վ� docker-compose.yml ��A�u�ݭn�b���s���� docker-compose up -d ���O�A�A�ȴN�|���s�G�p�C
    
### �e�����q
    * ����ĳ�ϥίB��IP���q, ���ӱĥ�__�e���W��__�ө������q
    * Container �A�ȬO�g�b�P�@�� docker-compose.yml�ɮת��ܡA�Q�إ߰_�ӮɡA���q�A�ȬO�ۦP��
    * �p�G�O���Pdocker-compose.yml �إ߰_�Ӫ��A��, �h�O�z�L�إ� network �ӷ��q
    
### Harbor
    * �x�s�ζ��p���� image�AHarbor ���ѤF²���� UI �����A�]�t�v�����ޡA�θ�������۰ʦP�B�\��
    * ���� Docker Registry
    
### CI/CD 
    * Developer ---git push---> Gitlab
    * Gitlab ---Webhook---> Jenkins
    * Jenkins ---rsyne---> Server
    
#### CI, Continuous Integration �����X
    * �{���ظm: �}�o�H���b�C�@���� Commit & Push ��A�������Τ@�����Ҧ۰� Build �{���A�z�L���@�B�J�i�H�קK�C�Ӷ}�o�H���]���������ҡ��M�󪩥����ۦP�A�y�� Service ���`�C
    * �{������: ��{���sĶ������A�N�|�z�L�u�椸���աv���շs�g���\��O�_���T�A�Ϊ̽T�{�O�_���v�T��{���\��A�z�L�ӨB�J�i����աA�i�H�קK���}�o�H����ѩ󥻾������ˬd�A�@���u�������ҡv�\�ΡC
    * �ت�:
        * �N�C�H���������I
        * ��֤H�u��ʪ����ШB�J
        * �i�檩���ި�
        * �W�[�t�Τ@�P�ʻP�z����
        * ��ֹζ� Loading
        
#### CD, Continuous Deployment ����G�p
    * �G�p�A��: �z�L�۰ʤƤ覡�A�N�g�n���{���X��s������W�ä��}��~�A�ȡA�t�~�ݭn�T�O�M�󪩥�&��Ʈw��Ƨ���ʡA�]�|�z�L�ʱ��t�ζi��A�Ȧs���ˬd�A�Y�A�Ȳ��`�ɷ|�Y�ɵo�e�q���i�ܶ}�o�H���C
    * �ت�: 
        * �O���C����s�{�����i���Z����
        * �T�O�A�Ȧs��
        
#### CICD �u�㤶��
    * GitLab (�����u��)
    * GitHub (�����u��)
    * Jenkins (�۰ʤƫظm�u��)
    * Drone (�۰ʤƫظm�u��)
    * Circle (�۰ʤƫظm�u��)
    * Docker (���t�G�p���Ҥu��)
    * K8S (�޲z Docker Container �u��)
    * Helm (�ֳt�ظm�U���� K8S �u��)
    * Grafana (�����ƾںʱ��u��)
    * ELK (Log �`���u��)
    * Telegram (�q�T�B���~�q���u��)
    * Slack (�q�T�B���~�q���u��)        
        