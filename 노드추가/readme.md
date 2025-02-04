맥 방화벽 끄기
`sudo /usr/libexec/ApplicationFirewall/socketfilterfw --setglobalstate off`

`kubelet kubeadm kubectl` 설치
`kubeadm init`
`sudo kubeadm token create --print-join-command` 토큰 발급

결과값 워커 노드 터미널에서 실행!
`kubectl get nod` 확인

윈도우, mac  kubelet 실행이 안됨 -> 워커 노드 역할만 가능 