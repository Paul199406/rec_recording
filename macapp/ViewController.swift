//
//  ViewController.swift
//  macapp
//
//  Created by jiweiLi on 2020/12/12.
//  Copyright © 2020 jiweiLi. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {

    var recStatus:Bool = false;
    var thread:Thread?;//
    let btn = NSButton.init(title: "button", target: nil, action: nil);
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        //设置窗口大小
        self.view.setFrameSize(NSSize(width:320,height:240));
        
        //添加控件
        btn.title = "开始录制";//
        btn.frame = NSRect(x:100,y:100,width: 120,height: 50);//显示位置 mac app 原点在左下角不是在左上角
        btn.setButtonType(.pushOnPushOff);
        
        //设置控件回调函数callback func：注意：回调函数前要加 @objc 
        btn.target = self;
        btn.action = #selector(myfunc);
        
        //添加子控件
        self.view.addSubview(btn);
        
        
    }
    
    @objc
    func myfunc(){
        
        self.recStatus = !self.recStatus;
        if recStatus {
            
            thread = Thread.init(target: self,
                                 selector: #selector(self.recAudio),
                                 object: nil);
            
            thread?.start();
            btn.title = "停止录制";
        } else{
            set_status(0);
            btn.title = "开始录制";
        }
       // rec_audio();
    }

    @objc func recAudio() {
        
        print("start")
        rec_vedio();
    }
    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }


}

