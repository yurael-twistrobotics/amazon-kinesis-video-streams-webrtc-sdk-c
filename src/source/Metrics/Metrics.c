/**
 * Kinesis WebRTC Metrics
 */
#define LOG_CLASS "Metrics"
#include "../Include_i.h"

STATUS logIceServerMetrics(PRtcIceServerStats pRtcIceServerStats)
{
    STATUS retStatus = STATUS_SUCCESS;
    CHK(pRtcIceServerStats != NULL, STATUS_NULL_ARG);
    DLOGD("ICE Server URL: %s", pRtcIceServerStats->url);
    DLOGD("ICE Server port: %d", pRtcIceServerStats->port);
    DLOGD("ICE Server protocol: %s", pRtcIceServerStats->protocol);
    DLOGD("Total requests sent:%" PRIu64, pRtcIceServerStats->totalRequestsSent);
    DLOGD("Total responses received: %" PRIu64, pRtcIceServerStats->totalResponsesReceived);
    DLOGD("Total round trip time: %" PRIu64 "ms", pRtcIceServerStats->totalRoundTripTime / HUNDREDS_OF_NANOS_IN_A_MILLISECOND);
CleanUp:
    return retStatus;
}

STATUS logIceCandidateMetrics(PRtcIceCandidateStats pRtcIceCandidateStats, BOOL isLocal)
{
    STATUS retStatus = STATUS_SUCCESS;
    CHK(pRtcIceCandidateStats != NULL, STATUS_NULL_ARG);
    if (isLocal) {
        DLOGD("=========Local candidate stats=========");
        DLOGD("Candidate relay protocol: %s", pRtcIceCandidateStats->relayProtocol);
        DLOGD("Candidate Ice server source: %s", pRtcIceCandidateStats->url);
    } else {
        DLOGD("=========Remote candidate stats=========");
    }
    DLOGD("Candidate IP Address: %s", pRtcIceCandidateStats->address);
    DLOGD("Candidate type: %s", pRtcIceCandidateStats->candidateType);
    DLOGD("Candidate port: %d", pRtcIceCandidateStats->port);
    DLOGD("Candidate priority: %d", pRtcIceCandidateStats->priority);
    DLOGD("Candidate transport protocol: %s", pRtcIceCandidateStats->protocol);

CleanUp:
    return retStatus;
}

STATUS getIceCandidatePairStats(PRtcPeerConnection pRtcPeerConnection, PRtcIceCandidatePairStats pRtcIceCandidatePairStats)
{
    STATUS retStatus = STATUS_SUCCESS;
    PKvsPeerConnection pKvsPeerConnection = (PKvsPeerConnection) pRtcPeerConnection;
    UNUSED_PARAM(pKvsPeerConnection);
    CHK((pRtcPeerConnection != NULL || pRtcIceCandidatePairStats != NULL), STATUS_NULL_ARG);
    CHK(FALSE, STATUS_NOT_IMPLEMENTED);
CleanUp:
    return retStatus;
}

STATUS getIceCandidateStats(PRtcPeerConnection pRtcPeerConnection, PRtcIceCandidateStats pRtcIceCandidateStats, BOOL isLocal)
{
    STATUS retStatus = STATUS_SUCCESS;
    PIceAgent pIceAgent = ((PKvsPeerConnection) pRtcPeerConnection)->pIceAgent;
    CHK((pRtcPeerConnection != NULL || pRtcIceCandidateStats != NULL), STATUS_NULL_ARG);
    if (isLocal) {
        STRCPY(pRtcIceCandidateStats->address, pIceAgent->rtcSelectedLocalIceCandidateDiagnostics.address);
        STRCPY(pRtcIceCandidateStats->candidateType, pIceAgent->rtcSelectedLocalIceCandidateDiagnostics.candidateType);
        pRtcIceCandidateStats->port = pIceAgent->rtcSelectedLocalIceCandidateDiagnostics.port;
        pRtcIceCandidateStats->priority = pIceAgent->rtcSelectedLocalIceCandidateDiagnostics.priority;
        STRCPY(pRtcIceCandidateStats->protocol, pIceAgent->rtcSelectedLocalIceCandidateDiagnostics.protocol);
        STRCPY(pRtcIceCandidateStats->relayProtocol, pIceAgent->rtcSelectedLocalIceCandidateDiagnostics.relayProtocol);
        STRCPY(pRtcIceCandidateStats->url, pIceAgent->rtcSelectedLocalIceCandidateDiagnostics.url);
    } else {
        STRCPY(pRtcIceCandidateStats->address, pIceAgent->rtcSelectedRemoteIceCandidateDiagnostics.address);
        STRCPY(pRtcIceCandidateStats->candidateType, pIceAgent->rtcSelectedRemoteIceCandidateDiagnostics.candidateType);
        pRtcIceCandidateStats->port = pIceAgent->rtcSelectedRemoteIceCandidateDiagnostics.port;
        pRtcIceCandidateStats->priority = pIceAgent->rtcSelectedRemoteIceCandidateDiagnostics.priority;
        STRCPY(pRtcIceCandidateStats->protocol, pIceAgent->rtcSelectedRemoteIceCandidateDiagnostics.protocol);
    }
CleanUp:
    return retStatus;
}

STATUS getIceServerStats(PRtcPeerConnection pRtcPeerConnection, PRtcIceServerStats pRtcIceServerStats)
{
    STATUS retStatus = STATUS_SUCCESS;
    PIceAgent pIceAgent = ((PKvsPeerConnection) pRtcPeerConnection)->pIceAgent;
    CHK((pRtcPeerConnection != NULL && pRtcIceServerStats != NULL), STATUS_NULL_ARG);
    CHK(pRtcIceServerStats->iceServerIndex < pIceAgent->iceServersCount, STATUS_ICE_SERVER_INDEX_INVALID);

    pRtcIceServerStats->port = pIceAgent->rtcIceServerDiagnostics[pRtcIceServerStats->iceServerIndex].port;
    STRCPY(pRtcIceServerStats->protocol, pIceAgent->rtcIceServerDiagnostics[pRtcIceServerStats->iceServerIndex].protocol);
    STRCPY(pRtcIceServerStats->url, pIceAgent->rtcIceServerDiagnostics[pRtcIceServerStats->iceServerIndex].url);
    pRtcIceServerStats->totalRequestsSent = pIceAgent->rtcIceServerDiagnostics[pRtcIceServerStats->iceServerIndex].totalRequestsSent;
    pRtcIceServerStats->totalResponsesReceived = pIceAgent->rtcIceServerDiagnostics[pRtcIceServerStats->iceServerIndex].totalResponsesReceived;
    pRtcIceServerStats->totalRoundTripTime = pIceAgent->rtcIceServerDiagnostics[pRtcIceServerStats->iceServerIndex].totalRoundTripTime;
CleanUp:
    return retStatus;
}

STATUS getTransportStats(PRtcPeerConnection pRtcPeerConnection, PRtcTransportStats pRtcTransportStats)
{
    STATUS retStatus = STATUS_SUCCESS;
    PKvsPeerConnection pKvsPeerConnection = (PKvsPeerConnection) pRtcPeerConnection;
    UNUSED_PARAM(pKvsPeerConnection);
    CHK(pRtcPeerConnection != NULL || pRtcTransportStats != NULL, STATUS_NULL_ARG);
    CHK(FALSE, STATUS_NOT_IMPLEMENTED);
CleanUp:
    return retStatus;
}

STATUS getRtpRemoteInboundStats(PRtcPeerConnection pRtcPeerConnection, PRtcRtpTransceiver pTransceiver,
                                PRtcRemoteInboundRtpStreamStats pRtcRemoteInboundRtpStreamStats)
{
    STATUS retStatus = STATUS_SUCCESS;
    PDoubleListNode node = NULL;
    PKvsPeerConnection pKvsPeerConnection = (PKvsPeerConnection) pRtcPeerConnection;
    CHK(pRtcPeerConnection != NULL || pRtcRemoteInboundRtpStreamStats != NULL, STATUS_NULL_ARG);
    PKvsRtpTransceiver pKvsRtpTransceiver = (PKvsRtpTransceiver) pTransceiver;
    if (pKvsRtpTransceiver == NULL) {
        CHK_STATUS(doubleListGetHeadNode(pKvsPeerConnection->pTransceievers, &node));
        CHK_STATUS(doubleListGetNodeData(node, (PUINT64) &pKvsRtpTransceiver));
        CHK(pKvsRtpTransceiver != NULL, STATUS_NOT_FOUND);
    }
    // check if specified transceiver belongs to this connection
    CHK_STATUS(hasTransceiverWithSsrc(pKvsPeerConnection, pKvsRtpTransceiver->sender.ssrc));
    MUTEX_LOCK(pKvsRtpTransceiver->sender.statsLock);
    *pRtcRemoteInboundRtpStreamStats = pKvsRtpTransceiver->sender.remoteInboundStats;
    MUTEX_UNLOCK(pKvsRtpTransceiver->sender.statsLock);
CleanUp:
    return retStatus;
}

STATUS getRtpOutboundStats(PRtcPeerConnection pRtcPeerConnection, PRtcRtpTransceiver pTransceiver,
                           PRtcOutboundRtpStreamStats pRtcOutboundRtpStreamStats)
{
    STATUS retStatus = STATUS_SUCCESS;
    PDoubleListNode node = NULL;
    PKvsPeerConnection pKvsPeerConnection = (PKvsPeerConnection) pRtcPeerConnection;
    CHK(pRtcPeerConnection != NULL || pRtcOutboundRtpStreamStats != NULL, STATUS_NULL_ARG);
    PKvsRtpTransceiver pKvsRtpTransceiver = (PKvsRtpTransceiver) pTransceiver;
    if (pKvsRtpTransceiver == NULL) {
        CHK_STATUS(doubleListGetHeadNode(pKvsPeerConnection->pTransceievers, &node));
        CHK_STATUS(doubleListGetNodeData(node, (PUINT64) &pKvsRtpTransceiver));
        CHK(pKvsRtpTransceiver != NULL, STATUS_NOT_FOUND);
    }
    // check if specified transceiver belongs to this connection
    CHK_STATUS(hasTransceiverWithSsrc(pKvsPeerConnection, pKvsRtpTransceiver->sender.ssrc));
    MUTEX_LOCK(pKvsRtpTransceiver->sender.statsLock);
    *pRtcOutboundRtpStreamStats = pKvsRtpTransceiver->sender.outboundStats;
    MUTEX_UNLOCK(pKvsRtpTransceiver->sender.statsLock);
CleanUp:
    return retStatus;
}

STATUS rtcPeerConnectionGetMetrics(PRtcPeerConnection pRtcPeerConnection, PRtcRtpTransceiver pRtcRtpTransceiver, PRtcStats pRtcMetrics)
{
    STATUS retStatus = STATUS_SUCCESS;
    CHK(pRtcPeerConnection != NULL && pRtcMetrics != NULL, STATUS_NULL_ARG);
    switch (pRtcMetrics->requestedTypeOfStats) {
        case RTC_STATS_TYPE_CANDIDATE_PAIR:
            getIceCandidatePairStats(pRtcPeerConnection, &pRtcMetrics->rtcStatsObject.iceCandidatePairStats);
            break;
        case RTC_STATS_TYPE_LOCAL_CANDIDATE:
            CHK_STATUS(getIceCandidateStats(pRtcPeerConnection, &pRtcMetrics->rtcStatsObject.localIceCandidateStats, TRUE));
            if (NULL != getenv(LOG_STATS)) {
                DLOGD("ICE local candidate Stats requested at %" PRIu64, pRtcMetrics->timestamp);
                logIceCandidateMetrics(&pRtcMetrics->rtcStatsObject.localIceCandidateStats, TRUE);
            }
            break;
        case RTC_STATS_TYPE_REMOTE_CANDIDATE:
            CHK_STATUS(getIceCandidateStats(pRtcPeerConnection, &pRtcMetrics->rtcStatsObject.remoteIceCandidateStats, FALSE));
            if (NULL != getenv(LOG_STATS)) {
                DLOGD("ICE remote candidate Stats requested at %" PRIu64, pRtcMetrics->timestamp);
                logIceCandidateMetrics(&pRtcMetrics->rtcStatsObject.remoteIceCandidateStats, FALSE);
            }
            break;
        case RTC_STATS_TYPE_TRANSPORT:
            getTransportStats(pRtcPeerConnection, &pRtcMetrics->rtcStatsObject.transportStats);
            break;
        case RTC_STATS_TYPE_REMOTE_INBOUND_RTP:
            getRtpRemoteInboundStats(pRtcPeerConnection, pRtcRtpTransceiver, &pRtcMetrics->rtcStatsObject.remoteInboundRtpStreamStats);
            break;
        case RTC_STATS_TYPE_OUTBOUND_RTP:
            getRtpOutboundStats(pRtcPeerConnection, pRtcRtpTransceiver, &pRtcMetrics->rtcStatsObject.outboundRtpStreamStats);
            break;
        case RTC_STATS_TYPE_ICE_SERVER:
            pRtcMetrics->timestamp = GETTIME();
            CHK_STATUS(getIceServerStats(pRtcPeerConnection, &pRtcMetrics->rtcStatsObject.iceServerStats));
            if (NULL != getenv(LOG_STATS)) {
                DLOGD("ICE Server Stats requested at %" PRIu64, pRtcMetrics->timestamp);
                logIceServerMetrics(&pRtcMetrics->rtcStatsObject.iceServerStats);
            }
            break;
        case RTC_STATS_TYPE_CERTIFICATE:
        case RTC_STATS_TYPE_CSRC:
        case RTC_STATS_TYPE_INBOUND_RTP:
        case RTC_STATS_TYPE_REMOTE_OUTBOUND_RTP:
        case RTC_STATS_TYPE_PEER_CONNECTION:
        case RTC_STATS_TYPE_DATA_CHANNEL:
        case RTC_STATS_TYPE_RECEIVER:
        case RTC_STATS_TYPE_SENDER:
        case RTC_STATS_TYPE_TRACK:
        case RTC_STATS_TYPE_CODEC:
        case RTC_STATS_TYPE_SCTP_TRANSPORT:
        case RTC_STATS_TYPE_TRANSCEIVER:
        case RTC_STATS_TYPE_RTC_ALL:
        default:
            CHK(FALSE, STATUS_NOT_IMPLEMENTED);
    }
CleanUp:
    CHK_LOG_ERR(retStatus);
    return retStatus;
}
