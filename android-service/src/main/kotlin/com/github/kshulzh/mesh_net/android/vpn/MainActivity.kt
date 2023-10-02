package com.github.kshulzh.mesh_net.android.vpn

import android.app.Activity
import android.content.Intent
import android.net.VpnService
import android.os.Bundle
import android.widget.Button
import com.example.myapplication.R

class MainActivity : Activity() {
    private val VPN_REQUEST_CODE = 0x0F

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val turnOn = findViewById<Button>(R.id.turn_on)
        turnOn.setOnClickListener {
            startVpn()
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == VPN_REQUEST_CODE && resultCode == RESULT_OK) {
            //waitingForVPNStart = true;
            startService(Intent(this, LocalVpnService::class.java))
            //enableButton(false);
        }
    }

    private fun startVpn() {
        val vpnIntent = VpnService.prepare(this)
        if (vpnIntent != null) startActivityForResult(
            vpnIntent,
            VPN_REQUEST_CODE
        ) else onActivityResult(VPN_REQUEST_CODE, RESULT_OK, null)
    }
}