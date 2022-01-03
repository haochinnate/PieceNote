# Deploying

- 這邊不需要整個 VM, we are not executing any coe
- 如果有 Node JS API 的話, 就需要VM 在上面跑

## Deployment-Vercel

1. Sign up at vercel.com
2. Install the Vercel CLI
3. Run 'vercel' in our project directory

```cmd
> cd \reactplayground\pics

> npm install -g vercel

> vercel login
  account
  password

> vercel
  第一次會問一些東西, 全部按 enter 選 default
  跑完會有連結, 

// 如果有修改後要 redeploy
> vercel --prod

// 如果有失敗
// 去 Vercel project 的 setting 設定 BUILD COMMAND
CI=false npm run build 

```

- https://pics-haochinnate.vercel.app/

## Deployment-Netlify

- npm run build

- 更新後上傳 Github, 自動 rebuild

- https://fervent-goldwasser-769b22.netlify.app/

