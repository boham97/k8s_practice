calico 플러그 인 설치
`kubectl apply -f https://docs.projectcalico.org/manifests/calico.yaml`

대시보드 접근
`kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.6.1/aio/deploy/recommended.yaml`
`kubectl proxy`

118p kubeadm은 맥에서 하자!

kubectl config
`kubectl config view --minify`
수정
`kubectl config set-context --current --namespace=kube-system`

nginx를 수동으로 켜보자

- kubectl run nginx-app --image nginx --port=80
- kubectl get pods
- kubectl.exe  get service
- kubectl delete pod nginx-app
- kubectl delete svc nginx-app


다른 네임스페이스 조회 
`kubectl run nginx --image=nginx --namespace=test --port=80`
`kubectl get pods --all-namespaces`
`kubectl get pod -n test`

`kubectl get replicaset`
`kubectl get deployment`
`kubectl get service`
업데이트 확인
`kubectl rollout status deployment.apps/nginx-deploy`

레플리카 확인
`kbuectl get rs`

히스토리 설정 및 롤백
`kubectl annotate deployment.apps/nginx-deploy kubernetes.io/chang-cause="iamge uddated"`
`kubectl rollout history deployment.apps/nginx-deploy`
`kubectl rollout undo deploymenty.apps/nginx-deploy`